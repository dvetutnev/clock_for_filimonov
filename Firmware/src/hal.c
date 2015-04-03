#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal.h"

void hal_init(void)
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
	sei();
	return;
}

void hal_timer_init(void (*callback)(void))
{
	return;
}

void hal_led_off(void)
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

void hal_led_set(uint8_t value)
{
	hal_led_off();
	if ( value & SEGMENT_A ) SEGMENT_A_PORT |= _BV (SEGMENT_A_PIN);
	if ( value & SEGMENT_B ) SEGMENT_B_PORT |= _BV (SEGMENT_B_PIN);
	if ( value & SEGMENT_C ) SEGMENT_C_PORT |= _BV (SEGMENT_C_PIN);
	if ( value & SEGMENT_D ) SEGMENT_D_PORT |= _BV (SEGMENT_D_PIN);
	if ( value & SEGMENT_E ) SEGMENT_E_PORT |= _BV (SEGMENT_E_PIN);
	if ( value & SEGMENT_F ) SEGMENT_F_PORT |= _BV (SEGMENT_F_PIN);
	if ( value & SEGMENT_G ) SEGMENT_G_PORT |= _BV (SEGMENT_G_PIN);
	return;
}

void hal_led_number_off(void)
{
	NUMBER_DIGIT_0_PORT &= ~_BV (NUMBER_DIGIT_0_PIN);
	NUMBER_DIGIT_1_PORT &= ~_BV (NUMBER_DIGIT_1_PIN);
	NUMBER_DIGIT_2_PORT &= ~_BV (NUMBER_DIGIT_2_PIN);
	NUMBER_DIGIT_3_PORT &= ~_BV (NUMBER_DIGIT_3_PIN);
	NUMBER_DIGIT_4_PORT &= ~_BV (NUMBER_DIGIT_4_PIN);
	return;
}

void hal_led_number_set(uint8_t value)
{
	if ( value > MAX_NUMBER_DIGIT )	return;
	hal_led_number_off();
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

void hal_alarm_set(uint8_t value)
{
	if ( value ) ALARM_PORT |= _BV (ALARM_PIN); else ALARM_PORT &= ~_BV (ALARM_PIN);
	return;
}

uint8_t hal_key_get(void)
{
	return bit_is_set(KEY_PORT, KEY_PIN);
}

void lk_tick(void);
ISR (TIMER0_OVF_vect)
{
	lk_tick();
}

void hal_iic_init(void)
{
	return;
}

void hal_iic_stop(void)
{
	return;
}

uint8_t hal_iic_start(uint8_t addr)
{
	return 0;
}

uint8_t hal_iic_rep_start(uint8_t addr)
{
	return 0;
}

void hal_iic_start_wait(uint8_t addr)
{
	return;
}

uint8_t hal_iic_write(uint8_t data)
{
	return 0;
}

uint8_t hal_iic_read_ack(void)
{
	return 0;
}

uint8_t hal_iic_read_nak(void)
{
	return 0;
}

uint8_t hal_iic_read(uint8_t ack)
{
	return 0;
}

