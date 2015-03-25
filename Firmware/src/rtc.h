#ifndef RTC_H
#define RTC_H

#define DS1307
#ifdef DS1307
#define IIC_ADDRESS 0x68U //1101000
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
void rtc_get(rtc_time_t *time);
void rtc_set(const rtc_time_t *time);

#endif //RTC_H