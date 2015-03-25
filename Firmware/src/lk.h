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
#define LK_LED_OFF 0U
#define LK_LED_ON 1U
#define LK_LED_BLINK 2U
#define LK_LED_BLINK_DELAY 200U // ms
void lk_set_digit_state(uint8_t number, uint8_t state); 
void lk_set_ddot(uint8_t state);
void lk_set_aled(uint8_t number, uint8_t state); 
void lk_set_alarm(uint8_t state);
// Кнопки
#define LK_KEY_UP 0U
#define LK_KEY_DOWN 1U
#define LK_KEY_CLOCK_SET 2U
#define LK_KEY_ALARM_SET 3U
#define LK_KEY_ALARM_ENABLE 4U
// Состояние кнопки
#define LK_KEY_OFF 0U // Отпущена
#define LK_KEY_ON 1U // Нажата
// Задержки
#define LK_KEY_DELAY 50U // ms
uint8_t lk_get_key(uint8_t number);

#endif //BLINK_H