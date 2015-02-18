#include <avr/io.h>
#include <util/delay.h>

//#include "utils.h"

#include "blink.h"

#define LED      PD5
#define LED_DDR  DDRD
#define LED_PORT PORTD

#define BTN      PB1   // pin number
#define BTN_DDR  DDRB  // data direction
#define BTN_PORT PORTB // for OUTPUT write
#define BTN_PIN  PINB  // for INPUT read

#define DELAYTIME 300

int main(void)
{
    DDRD  = 0xFF; // all ports on D to OUTPUT
    DDRB  = 0xFF; // all ports on B to OUTPUT
    PORTD = 0x0;  // all ports on D to LOW
    PORTB = 0x0;  // all ports on B to LOW

    //cbi(BTN_DDR, BTN);          // set BTN port to INPUT
    //sbi(BTN_PORT, BTN); // activate pull-up resistor on BTN

    while ( 1 ) {
		
		blink ();
             //sbi(LED_PORT, LED); // OUTPUT to HIGH
			 //LED_PORT |= _BV(LED);
            //_delay_ms(DELAYTIME);

            //cbi(LED_PORT, LED); // OUTPUT to LOW
			//LED_PORT &= ~(_BV(LED));
            //_delay_ms(DELAYTIME);
        
    }
}