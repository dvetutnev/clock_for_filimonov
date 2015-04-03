#ifndef RTC_H
#define RTC_H

#define DS1307
#ifdef DS1307
#define IIC_ADDRESS 0x68U //1101000
#define IIC_TIME_OFFSET 0x0U
#define IIC_ALARM_OFFSET 0x08U
#define IIC_ALARM_STATE_OFFSET 0x0bU
#define IIC_READ 0x01U
#define IIC_WRITE 0x00U
#define HOUR_ADDRESS 0x02U
#define MINUTE_ADDRESS 0x01U
#define SECOND_ADDRESS 0x01U
#endif //DS1307

typedef struct
{
	uint8_t hour_10;
	uint8_t hour;
	uint8_t minute_10;
	uint8_t minute;
	uint8_t second_10;
	uint8_t second;
} rtc_time_t;

void rtc_init(void);
void rtc_get(rtc_time_t* time);
void rtc_set(const rtc_time_t* time);
void rtc_get_alarm(rtc_time_t* time);
void rtc_set_alarm(const rtc_time_t* time);
uint8_t rtc_get_alarm_state(void);
void rtc_set_alarm_state(const uint8_t state);

#endif //RTC_H