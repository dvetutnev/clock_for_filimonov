// HAL module
#ifndef HAL_H
#define HAL_H

#define SEGMENT_A 0x80
#define SEGMENT_A_PIN 6
#define SEGMENT_A_PORT PORTB
#define SEGMENT_A_DDR DDRB
#define SEGMENT_B 0x40
#define SEGMENT_B_PIN 6
#define SEGMENT_B_PORT PORTD
#define SEGMENT_B_DDR DDRD
#define SEGMENT_C 0x20
#define SEGMENT_C_PIN 0
#define SEGMENT_C_PORT PORTB
#define SEGMENT_C_DDR DDRB
#define SEGMENT_D 0x10
#define SEGMENT_D_PIN 2
#define SEGMENT_D_PORT PORTB
#define SEGMENT_D_DDR DDRB
#define SEGMENT_E 0x8
#define SEGMENT_E_PIN 1
#define SEGMENT_E_PORT PORTB
#define SEGMENT_E_DDR DDRB
#define SEGMENT_F 0x4
#define SEGMENT_F_PIN 7
#define SEGMENT_F_PORT PORTB
#define SEGMENT_F_DDR DDRB
#define SEGMENT_G 0x2
#define SEGMENT_G_PIN 7
#define SEGMENT_G_PORT PORTD
#define SEGMENT_G_DDR DDRD

#define SEGMENT_ADD_0 SEGMENT_A
#define SEGMENT_ADD_1 SEGMENT_D
#define SEGMENT_ADD_2 SEGMENT_E
#define SEGMENT_ADD_3 SEGMENT_F

#define SEGMENT_DOT_0 SEGMENT_B
#define SEGMENT_DOT_1 SEGMENT_C

#define NUMBER_DIGIT_0_PIN 3
#define NUMBER_DIGIT_0_PORT PORTC
#define NUMBER_DIGIT_0_DDR DDRC
#define NUMBER_DIGIT_1_PIN 2
#define NUMBER_DIGIT_1_PORT PORTC
#define NUMBER_DIGIT_1_DDR DDRC
#define NUMBER_DIGIT_2_PIN 4
#define NUMBER_DIGIT_2_PORT PORTB
#define NUMBER_DIGIT_2_DDR DDRB
#define NUMBER_DIGIT_3_PIN 3
#define NUMBER_DIGIT_3_PORT PORTB
#define NUMBER_DIGIT_3_DDR DDRB
#define NUMBER_DIGIT_4_PIN 1
#define NUMBER_DIGIT_4_PORT PORTC
#define NUMBER_DIGIT_4_DDR DDRC

#define MAX_NUMBER_DIGIT 4 // Нумерация от 0
#define NUMBER_NOT_DIGIT MAX_NUMBER_DIGIT // Последний разряд двоеточие и дополнительные светодиоды

#define KEY_PIN 3
#define KEY_PORT PIND
#define KEY_DDR DDRD

#define ALARM_PIN 5
#define ALARM_PORT PORTD
#define ALARM_DDR DDRD

// Interface
void hal_init (void);
void hal_led_off (void);
void hal_led_set (uint8_t value);
void hal_led_number_off (void);
void hal_led_number_set (uint8_t value);
uint8_t hal_digit_to_7code (uint8_t value);

void hal_alarm_set (uint8_t value);

uint8_t hal_key_get (void);


#endif // HAL_H