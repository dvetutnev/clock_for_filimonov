#include <stdint.h>
#include "rtc.h"
#include "hal.h"

void rtc_init(void)
{
	hal_iic_init();
	return;
}

void rtc_get(rtc_time_t *time)
{
	if ( time == NULL ) return;
	#ifdef DS1307
	uint8_t hour, minute, second;
	hal_iic_start(IIC_ADDRESS+IIC_WRITE);
	hal_iic_write(0);
	hal_iic_rep_start(IIC_ADDRESS+IIC_READ);
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
	return;
}

void rtc_set(const rtc_time_t *time)
{
	if ( time == NULL ) return;
	#ifdef DS1307
	hal_iic_start(IIC_ADDRESS+IIC_WRITE);
	hal_iic_write(0);
	hal_iic_write( (time->second_10 << 4) | time->second );
	hal_iic_write( (time->minute_10 << 4) | time->minute );
	hal_iic_write( (time->hour_10 << 4) | time->hour );
	hal_iic_stop();
	#endif //DS1307
	return;
}