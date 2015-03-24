//LED and key module
#include <stdint.h>
#include "lk.h"
#include "timer.h"
#include "hal.h"

static volatile uint8_t number_digit = 0; // Текущий разряд
static volatile uint8_t alarm_state = LK_LED_OFF; // Текущий разряд
static timer_object_t timer_lk_tick_object; //
static timer_object_t timer_lk_blink_object; // Таймер мигания
static uint8_t timer_lk_blink_state = 0; // Первый или второй проход таймера

static uint8_t lk_digit_to_7code_(uint8_t value); // Преобразование цифры в семисегментный код
static void lk_set_aled_state_(uint8_t bits, uint8_t state); // Установка состояния доп.светодиодов, общая
static void lk_blink_tick_(void); // Callback таймера мигания

// Разряды
typedef struct
{
	uint8_t value;
	uint8_t state;
} digit_t;
static digit_t digits[MAX_NUMBER_DIGIT + 1];

// Кнопки
typedef struct
{
	uint8_t value:1;
	uint8_t old_value:1;
	timer_object_t timer_object;
} key_t;
static key_t keys[MAX_NUMBER_DIGIT + 1];

void lk_init(void)
{
	for (uint8_t i = 0; i < MAX_NUMBER_DIGIT; i++)
	{
		digits[i].state = LK_LED_ON;
		digits[i].value = 0;
		keys[i].value = 0;
		keys[i].old_value = 0;
		keys[i].timer_object = timer_get_object(TIMER_LK_KEY_0 + i);
	};
	hal_led_off();
	hal_led_number_off();
	//
	timer_lk_tick_object = timer_get_object(TIMER_LK_TICK);
	timer_set_callback(timer_lk_tick_object, &lk_tick);
	timer_set(timer_lk_tick_object, 1);
	
	timer_lk_blink_object = timer_get_object(TIMER_LK_BLINK);
	timer_set_callback(timer_lk_blink_object, &lk_blink_tick_);
	timer_set(timer_lk_blink_object, LK_LED_BLINK_DELAY);
}

void lk_tick(void)
{
	hal_alarm_set(alarm_state);
	number_digit++;
	if ( number_digit > MAX_NUMBER_DIGIT) number_digit = 0;
	hal_led_off();
	hal_led_number_set(number_digit);
	if ( number_digit == NUMBER_NOT_DIGIT )
	{	// Доп. светодиоды
		if ( timer_lk_blink_state )	hal_led_set(digits[number_digit].value); else hal_led_set(digits[number_digit].value & ~digits[number_digit].state );
	} 
	else
	{	// Цифры
		switch ( digits[number_digit].state )
		{
			case LK_LED_OFF:
				hal_led_set(0);
				break;
			case LK_LED_ON:
				hal_led_set(digits[number_digit].value);
				break;
			case LK_LED_BLINK:
				if ( timer_lk_blink_state ) hal_led_set(digits[number_digit].value); else hal_led_set(0);
		};
	};
	// Обработка кнопок
	uint8_t key;
	key = hal_key_get();
	if ( keys[number_digit].old_value != key )
	{
		keys[number_digit].old_value = key;
		timer_set(keys[number_digit].timer_object, LK_KEY_DELAY);
	}
	else if ( !(timer_get(keys[number_digit].timer_object)) ) keys[number_digit].value = key;
	// Перезапуск таймера
	timer_set(timer_lk_tick_object, 1);
}

void lk_set_digit(uint8_t number, uint8_t value)
{
	if ( number <= MAX_NUMBER_DIGIT && number != NUMBER_NOT_DIGIT ) digits[number].value = lk_digit_to_7code_(value); // Только цифры
}

void lk_set_4digits(uint8_t value_0, uint8_t value_1, uint8_t value_2, uint8_t value_3)
{
	lk_set_digit(0, value_0);
	lk_set_digit(1, value_1);
	lk_set_digit(2, value_2);
	lk_set_digit(3, value_3);
}

void lk_set_digit_state(uint8_t number, uint8_t state)
{
	if ( number <= MAX_NUMBER_DIGIT && number != NUMBER_NOT_DIGIT // Только цифры
		&& (state == LK_LED_OFF || state == LK_LED_ON || state == LK_LED_BLINK) ) digits[number].state = state;
}

void lk_set_ddot(uint8_t state)
{
	lk_set_aled_state_(SEGMENT_DOT_0 | SEGMENT_DOT_1, state);
}

void lk_set_aled(uint8_t number, uint8_t state)
{
	switch (number)
	{
		case 0:
			number = SEGMENT_ADD_0;
			break;
		case 1:
			number = SEGMENT_ADD_1;
			break;
		case 2:
			number = SEGMENT_ADD_2;
			break;
		case 3:
			number = SEGMENT_ADD_3;
			break;
		default:
			return;
	};
	lk_set_aled_state_(number, state);
} //void lk_set_aled_state(uint8_t number, uint8_t state)

void lk_set_alarm(uint8_t state)
{
	alarm_state = state;
}

uint8_t lk_get_key(uint8_t number)
{
	return ( number <= MAX_NUMBER_DIGIT ) ? keys[number].value : LK_KEY_OFF;
}

#define DIGIT_0 SEGMENT_A*1 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*1 + SEGMENT_E*1 + SEGMENT_F*1 + SEGMENT_G*0
#define DIGIT_1 SEGMENT_A*0 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*0 + SEGMENT_E*0 + SEGMENT_F*0 + SEGMENT_G*0
#define DIGIT_2 SEGMENT_A*1 + SEGMENT_B*1 + SEGMENT_C*0 + SEGMENT_D*1 + SEGMENT_E*1 + SEGMENT_F*0 + SEGMENT_G*1
#define DIGIT_3 SEGMENT_A*1 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*1 + SEGMENT_E*0 + SEGMENT_F*0 + SEGMENT_G*1
#define DIGIT_4 SEGMENT_A*0 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*0 + SEGMENT_E*0 + SEGMENT_F*1 + SEGMENT_G*1
#define DIGIT_5 SEGMENT_A*1 + SEGMENT_B*0 + SEGMENT_C*1 + SEGMENT_D*1 + SEGMENT_E*0 + SEGMENT_F*1 + SEGMENT_G*1
#define DIGIT_6 SEGMENT_A*1 + SEGMENT_B*0 + SEGMENT_C*1 + SEGMENT_D*1 + SEGMENT_E*1 + SEGMENT_F*1 + SEGMENT_G*1
#define DIGIT_7 SEGMENT_A*1 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*0 + SEGMENT_E*0 + SEGMENT_F*0 + SEGMENT_G*0
#define DIGIT_8 SEGMENT_A*1 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*1 + SEGMENT_E*1 + SEGMENT_F*1 + SEGMENT_G*1
#define DIGIT_9 SEGMENT_A*1 + SEGMENT_B*1 + SEGMENT_C*1 + SEGMENT_D*1 + SEGMENT_E*0 + SEGMENT_F*1 + SEGMENT_G*1
#define DIGIT_E SEGMENT_A*1 + SEGMENT_B*0 + SEGMENT_C*0 + SEGMENT_D*1 + SEGMENT_E*0 + SEGMENT_F*0 + SEGMENT_G*1
static uint8_t lk_digit_to_7code_(uint8_t value)
{
	switch ( value )
	{
		case 0: return DIGIT_0;
		case 1: return DIGIT_1;
		case 2: return DIGIT_2;
		case 3: return DIGIT_3;
		case 4: return DIGIT_4;
		case 5: return DIGIT_5;
		case 6: return DIGIT_6;
		case 7: return DIGIT_7;
		case 8: return DIGIT_8;
		case 9: return DIGIT_9;
		default: return DIGIT_E;
	};
}

static void lk_set_aled_state_(uint8_t bits, uint8_t state)
{
	switch (state)
	{
		case LK_LED_OFF:
			digits[NUMBER_NOT_DIGIT].value &= ~bits;
			digits[NUMBER_NOT_DIGIT].state &= ~bits;
			break;
		case LK_LED_ON:
			digits[NUMBER_NOT_DIGIT].value |= bits;
			digits[NUMBER_NOT_DIGIT].state &= ~bits;
			break;
		case LK_LED_BLINK:
			digits[NUMBER_NOT_DIGIT].value |= bits;
			digits[NUMBER_NOT_DIGIT].state |= bits;
			break;
	};
} // static void lk_set_aled_state_(uint8_t bits, uint8_t state)

static void lk_blink_tick_(void)  // Callback таймера мигания
{
	timer_lk_blink_state = ~timer_lk_blink_state; // Инвертирование направления
	timer_set(timer_lk_blink_object, LK_LED_BLINK_DELAY); // Перезапуск таймера мигания
}