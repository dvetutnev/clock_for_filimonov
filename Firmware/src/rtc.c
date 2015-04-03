#include <stdint.h>
#include <stdlib.h>
#include "rtc.h"
#include "hal.h"

static void rtc_get_time_(const uint8_t address, rtc_time_t* time);
static void rtc_set_time_(const uint8_t address, const rtc_time_t* time);

void rtc_init(void)
{
	hal_iic_init();
}

void rtc_get(rtc_time_t* time)
{
	rtc_get_time_(IIC_TIME_OFFSET, time);
}

void rtc_set(const rtc_time_t* time)
{
	rtc_set_time_(IIC_TIME_OFFSET, time);
}

void rtc_get_alarm(rtc_time_t* time)
{
	rtc_get_time_(IIC_ALARM_OFFSET, time);
}

void rtc_set_alarm(const rtc_time_t* time)
{
	rtc_set_time_(IIC_ALARM_OFFSET, time);
}

uint8_t rtc_get_alarm_state(void)
{
	uint8_t ret = 0;
	#ifdef DS1307
	hal_iic_start(IIC_ADDRESS+IIC_WRITE);
	hal_iic_write(IIC_ALARM_STATE_OFFSET);
	hal_iic_rep_start(IIC_ADDRESS+IIC_READ);
	ret = hal_iic_read_nak();
	hal_iic_stop();
	#endif //DS1307
	return ret;
}

void rtc_set_alarm_state(const uint8_t state)
{
	#ifdef DS1307
	hal_iic_start(IIC_ADDRESS + IIC_WRITE);
	hal_iic_write(IIC_ALARM_STATE_OFFSET);
	hal_iic_write(state);
	hal_iic_stop();
	#endif //DS1307
}

static void rtc_get_time_(const uint8_t address, rtc_time_t* time)
{
	if ( time == NULL ) return;
	#ifdef DS1307
	hal_iic_start(IIC_ADDRESS+IIC_WRITE);
	hal_iic_write(address);
	hal_iic_rep_start(IIC_ADDRESS+IIC_READ);
	uint8_t hour, minute, second;
	second = hal_iic_read_ack();
	minute = hal_iic_read_ack();
	hour = hal_iic_read_nak();
	hal_iic_stop();
	time->second_10 = second >> 4;
	time->second = second & 0xf;
	time->minute_10 = minute >> 4;
	time->minute = minute & 0xf;
	time->hour_10 = hour >> 4;
	time->hour = hour & 0xf;
	#endif //DS1307
}

static void rtc_set_time_(const uint8_t address, const rtc_time_t* time)
{
	if ( time == NULL ) return;
	#ifdef DS1307
	hal_iic_start(IIC_ADDRESS + IIC_WRITE);
	hal_iic_write(address);
	hal_iic_write( (time->second_10 << 4) | time->second );
	hal_iic_write( (time->minute_10 << 4) | time->minute );
	hal_iic_write( (time->hour_10 << 4) | time->hour );
	hal_iic_stop();
	#endif //DS1307
}
