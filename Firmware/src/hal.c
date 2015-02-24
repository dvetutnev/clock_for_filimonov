#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal.h"

void hal_init (void)
{
	cli ();
	// Output pin
	DDRB = 0; PORTB = 0;
	DDRC = 0; PORTC = 0;
	DDRD = 0; PORTD = 0;
	// Segments
	SEGMENT_A_DDR |= _BV (SEGMENT_A_PIN);
	SEGMENT_A_PORT &= ~_BV (SEGMENT_A_PIN);
	SEGMENT_B_DDR |= _BV (SEGMENT_B_PIN);
	SEGMENT_B_PORT &= ~_BV (SEGMENT_B_PIN);
	SEGMENT_C_DDR |= _BV (SEGMENT_C_PIN);
	SEGMENT_C_PORT &= ~_BV (SEGMENT_C_PIN);
	SEGMENT_D_DDR |= _BV (SEGMENT_D_PIN);
	SEGMENT_D_PORT &= ~_BV (SEGMENT_D_PIN);
	SEGMENT_E_DDR |= _BV (SEGMENT_E_PIN);
	SEGMENT_E_PORT &= ~_BV (SEGMENT_E_PIN);
	SEGMENT_F_DDR |= _BV (SEGMENT_F_PIN);
	SEGMENT_F_PORT &= ~_BV (SEGMENT_F_PIN);
	SEGMENT_G_DDR |= _BV (SEGMENT_G_PIN);
	SEGMENT_G_PORT &= ~_BV (SEGMENT_G_PIN);
	// Number digits
	NUMBER_DIGIT_0_DDR |= _BV (NUMBER_DIGIT_0_PIN);
	NUMBER_DIGIT_0_PORT &= ~_BV (NUMBER_DIGIT_0_PIN);
	NUMBER_DIGIT_1_DDR |= _BV (NUMBER_DIGIT_1_PIN);
	NUMBER_DIGIT_1_PORT &= ~_BV (NUMBER_DIGIT_1_PIN);
	NUMBER_DIGIT_2_DDR |= _BV (NUMBER_DIGIT_2_PIN);
	NUMBER_DIGIT_2_PORT &= ~_BV (NUMBER_DIGIT_2_PIN);
	NUMBER_DIGIT_3_DDR |= _BV (NUMBER_DIGIT_3_PIN);
	NUMBER_DIGIT_3_PORT &= ~_BV (NUMBER_DIGIT_3_PIN);
	NUMBER_DIGIT_4_DDR |= _BV (NUMBER_DIGIT_4_PIN);
	NUMBER_DIGIT_4_PORT &= ~_BV (NUMBER_DIGIT_4_PIN);
	// Alarm
	ALARM_DDR |= _BV (ALARM_PIN);
	ALARM_PORT &= ~_BV (ALARM_PIN);
	// Key, input
	KEY_DDR &= ~_BV (KEY_PIN);
	KEY_PORT &= ~_BV (KEY_PIN);
	// Timer 0
	TCCR0 = 0;
	TCCR0 = 0<<CS00|1<<CS01|0<<CS02; //тактовая 1/1
	TIMSK = 0;
	TIMSK = 1<<TOIE0;
	sei ();
	return;
}

void hal_led_off (void)
{
	SEGMENT_A_PORT &= ~_BV (SEGMENT_A_PIN);
	SEGMENT_B_PORT &= ~_BV (SEGMENT_B_PIN);
	SEGMENT_C_PORT &= ~_BV (SEGMENT_C_PIN);
	SEGMENT_D_PORT &= ~_BV (SEGMENT_D_PIN);
	SEGMENT_E_PORT &= ~_BV (SEGMENT_E_PIN);
	SEGMENT_F_PORT &= ~_BV (SEGMENT_F_PIN);
	SEGMENT_G_PORT &= ~_BV (SEGMENT_G_PIN);
	return;
}

void hal_led_set (uint8_t value)
{
	hal_led_off ();
	if ( value & SEGMENT_A ) SEGMENT_A_PORT |= _BV (SEGMENT_A_PIN);
	if ( value & SEGMENT_B ) SEGMENT_B_PORT |= _BV (SEGMENT_B_PIN);
	if ( value & SEGMENT_C ) SEGMENT_C_PORT |= _BV (SEGMENT_C_PIN);
	if ( value & SEGMENT_D ) SEGMENT_D_PORT |= _BV (SEGMENT_D_PIN);
	if ( value & SEGMENT_E ) SEGMENT_E_PORT |= _BV (SEGMENT_E_PIN);
	if ( value & SEGMENT_F ) SEGMENT_F_PORT |= _BV (SEGMENT_F_PIN);
	if ( value & SEGMENT_G ) SEGMENT_G_PORT |= _BV (SEGMENT_G_PIN);
	return;
}

void hal_led_number_off (void)
{
	NUMBER_DIGIT_0_PORT &= ~_BV (NUMBER_DIGIT_0_PIN);
	NUMBER_DIGIT_1_PORT &= ~_BV (NUMBER_DIGIT_1_PIN);
	NUMBER_DIGIT_2_PORT &= ~_BV (NUMBER_DIGIT_2_PIN);
	NUMBER_DIGIT_3_PORT &= ~_BV (NUMBER_DIGIT_3_PIN);
	NUMBER_DIGIT_4_PORT &= ~_BV (NUMBER_DIGIT_4_PIN);
	return;
}

void hal_led_number_set (uint8_t value)
{
	if ( value > MAX_NUMBER_DIGIT )	return;
	hal_led_number_off ();
	switch ( value )
	{
		case 0:
			NUMBER_DIGIT_0_PORT |= _BV (NUMBER_DIGIT_0_PIN);
			break;
		case 1:
			NUMBER_DIGIT_1_PORT |= _BV (NUMBER_DIGIT_1_PIN);
			break;
		case 2:
			NUMBER_DIGIT_2_PORT |= _BV (NUMBER_DIGIT_2_PIN);
			break;
		case 3:
			NUMBER_DIGIT_3_PORT |= _BV (NUMBER_DIGIT_3_PIN);
			break;
		case 4:
			NUMBER_DIGIT_4_PORT |= _BV (NUMBER_DIGIT_4_PIN);
			break;
		default:
			break;
	};
	return;
}

void hal_alarm_set (uint8_t value)
{
	if ( value ) ALARM_PORT |= _BV (ALARM_PIN); else ALARM_PORT &= ~_BV (ALARM_PIN);
	return;
}

uint8_t hal_key_get (void)
{
	return bit_is_set (KEY_PORT, KEY_PIN);
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
uint8_t hal_digit_to_7code (uint8_t value)
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

void lk_tick (void);
ISR (TIMER0_OVF_vect)
{
	lk_tick ();
}

