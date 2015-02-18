#include "blink.h"

#include <avr/io.h>
#include <util/delay.h>

#define LED      PD5
#define LED_DDR  DDRD
#define LED_PORT PORTD

#define BTN      PB1   // pin number
#define BTN_DDR  DDRB  // data direction
#define BTN_PORT PORTB // for OUTPUT write
#define BTN_PIN  PINB  // for INPUT read

#define DELAYTIME 300

void blink (void) {
	LED_PORT |= _BV(LED);
	_delay_ms(DELAYTIME);
	LED_PORT &= ~(_BV(LED));
	_delay_ms(DELAYTIME);
}