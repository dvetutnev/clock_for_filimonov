//LED and key module
#ifndef BLINK_H
#define BLINK_H

// Interface
void lk_init(void); // Инициализация
void lk_tick(void); // callback тик от таймера
// Цифры, нумерация с нуля
void lk_set_digit(uint8_t number, uint8_t value); // Вывести одну цифру
void lk_set_4digits(uint8_t value_0, uint8_t value_1, uint8_t value_2, uint8_t value_3); // вывести 4 цифры
// Состояние светодиодов
#define LK_LED_OFF 0
#define LK_LED_ON 1
#define LK_LED_BLINK 2
#define LK_LED_BLINK_DELAY 200 // ms
void lk_set_digit_state(uint8_t number, uint8_t state); 
void lk_set_ddot(uint8_t state);
void lk_set_aled(uint8_t number, uint8_t state); 
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
// Задержки
#define LK_KEY_DELAY 50 // ms
uint8_t lk_get_key(uint8_t number);

#endif //BLINK_H