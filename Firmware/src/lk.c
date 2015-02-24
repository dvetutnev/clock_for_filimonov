//LED and key module

#include <stdint.h>
#include "lk.h"
#include "hal.h"

static volatile uint8_t number_digit; // Текущий разряд
static volatile uint32_t blink_timer; // Таймер мигания
static volatile uint8_t blink_timer_reverse; // Направление таймера мигания 0 up, 1 down

typedef struct
{
	uint8_t value;
	uint8_t state;
} digit_t;
static digit_t digits[MAX_NUMBER_DIGIT + 1];

typedef struct
{
	uint8_t state;
	uint8_t old_value;
	uint8_t timer_pressed;
	uint32_t timer_fixed;
} key_t;
static key_t keys[MAX_NUMBER_DIGIT + 1];

void lk_init (void)
{
	uint8_t i;
	number_digit = 0;
	blink_timer = 0;
	blink_timer_reverse = 0;
	for (i = 0; i < MAX_NUMBER_DIGIT; i++)
	{
		digits[i].state = LK_DIGIT_ON;
		digits[i].value = 0;
		keys[i].state = 0;
		keys[i].old_value = 0;
		keys[i].timer_pressed = 0;
		keys[i].timer_fixed = 0;
	};
	hal_led_off ();
	hal_led_number_off ();
	return;
}

void lk_tick (void)
{
	number_digit++;
	if ( number_digit > MAX_NUMBER_DIGIT) number_digit = 0;
	hal_led_off ();
	hal_led_number_set (number_digit);
	if ( number_digit == NUMBER_NOT_DIGIT )
	{
		return;
	};
	switch ( digits[number_digit].state )
	{
		case LK_DIGIT_OFF:
			break;
		case LK_DIGIT_ON:
			hal_led_set (digits[number_digit].value);
			break;
		case LK_DIGIT_BLINK:
			//if 
			break;
		default:
			break;
	};
	return;
}

void lk_set_digit (uint8_t number, uint8_t value)
{
	if ( number > MAX_NUMBER_DIGIT || number == NUMBER_NOT_DIGIT ) return; // Только цифры
	digits[number].value = hal_digit_to_7code (value);
}

void lk_set_4digits (uint8_t value_0, uint8_t value_1, uint8_t value_2, uint8_t value_3)
{
	lk_set_digit (0, value_0);
	lk_set_digit (1, value_1);
	lk_set_digit (2, value_2);
	lk_set_digit (3, value_3);
}

void lk_set_digit_state (uint8_t number, uint8_t state)
{
	if ( number > MAX_NUMBER_DIGIT ) return;
	switch (state)
	{
		case LK_DIGIT_OFF:
		case LK_DIGIT_ON:
		case LK_DIGIT_BLINK:
			digits[number].state = state;
			break;
		default:
			break;
	};
}

void lk_set_ddot (uint8_t state)
{
	return;
}

void lk_set_aled_state (uint8_t number, uint8_t state)
{
	return;
}

uint8_t lk_get_key (uint8_t number)
{
	if ( number > MAX_NUMBER_DIGIT ) return LK_KEY_OFF;
	return LK_KEY_OFF;
}
