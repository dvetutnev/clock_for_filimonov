﻿//LED and key module
#ifndef BLINK_H
#define BLINK_H

// Interface
void lk_init(void); // Инициализация
void lk_tick(void); // callback тик от таймера

// Цифры, нумерация с нуля
void lk_set_digit(uint8_t number, uint8_t value); // Вывести одну цифру
void lk_set_4digits(uint8_t value_0, uint8_t value_1, uint8_t value_2, uint8_t value_3); // вывести 4 цифры
// Состояние цифры
#define LK_DIGIT_OFF 0
#define LK_DIGIT_ON 1
#define LK_DIGIT_BLINK 2
void lk_set_digit_state(uint8_t number, uint8_t state); 

// Двоеточие
#define LK_DDOT_OFF 0
#define LK_DDOT_ON 1
#define LK_DDOT_BLINK 2
void lk_set_ddot(uint8_t state);

// Дополнительные светодиоды
#define LK_ALED_OFF 0
#define LK_ALED_ON 1
#define LK_ALED_BLINK 2
void lk_set_aled(uint8_t number, uint8_t state); 

// Дополнительные светодиоды
#define LK_ALARM_OFF 0
#define LK_ALARM_ON 1
#define LK_ALARM_BLINK 2
void lk_set_alarm(uint8_t state);

// Кнопки
#define LK_KEY_UP 0
#define LK_KEY_DOWN 1
#define LK_KEY_CLOCK_SET 2
#define LK_KEY_ALARM_SET 3
#define LK_KEY_ALARM_ENABLE 4
// Состояние кнопки
#define LK_KEY_OFF 0 // Отпущена
#define LK_KEY_ON 1 // Нажата
#define LK_KEY_FIXED 2 // Зафиксирована в нажатом состоянии (нажата больше чем пол секунды)
// Задержки
#define DELAY_RIPPLE F_CPU * 0.0001 // ~30ms
#define DELAY_FIXED F_CPU * 0.001 // ~300ms
uint8_t lk_get_key(uint8_t number);

#endif //BLINK_H