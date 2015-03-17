#include <stdint.h>
#include "hal.h"
#include "timer.h"
#include "lk.h"
#include "rtc.h"

rtc_time_t current_time, alarm_time;

void app_init(void)
{
	hal_init();
	timer_init();
	lk_init();
	rtc_init();
	
	alarm_time.hour_10 = 0;
	alarm_time.hour = 0;
	alarm_time.minute_10 = 0;
	alarm_time.minute = 0;
	alarm_time.second_10 = 0;
	alarm_time.second = 0;
	
	current_time.hour_10 = 0;
	current_time.hour = 0;
	current_time.minute_10 = 0;
	current_time.minute = 0;
	current_time.second_10 = 0;
	current_time.second = 0;
	
	//rtc_set(&current_time);
	lk_set_aled(0, LK_LED_BLINK);
	lk_set_digit_state(0, LK_LED_BLINK);
}

void app_run(void)
{
	#ifdef PC_BUILD
	pchal_tick();
	#endif //PC_BUILD
	rtc_get(&current_time);
	if ( current_time.second & 0x01 ) lk_set_ddot(LK_LED_ON); else lk_set_ddot(LK_LED_OFF);
	if ( current_time.second & 0x01 ) lk_set_alarm(LK_LED_ON); else lk_set_alarm(LK_LED_OFF);
	lk_set_4digits(current_time.hour_10, current_time.hour, current_time.minute_10, current_time.minute);
}
