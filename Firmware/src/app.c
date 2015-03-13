/*
#include <SDL2/SDL.h>
#include <stdint.h>
#include "app.h"
#include "hal.h"
#include "lk.h"
*/

#include <stdint.h>
#include "hal.h"
#include "timer.h"
#include "lk.h"
#include "rtc.h"

rtc_time_t current_time, alarm_time;

void app_init(void)
{
	hal_init();
	lk_init();
	rtc_init();
	
	alarm_time.hour_10 = 0;
	alarm_time.hour = 0;
	alarm_time.minute_10 = 0;
	alarm_time.minute = 0;
	alarm_time.second_10 = 0;
	alarm_time.second = 0;
	
	current_time.hour_10 = 0;
	current_time.hour = 2;
	current_time.minute_10 = 1;
	current_time.minute = 2;
	current_time.second_10 = 0;
	current_time.second = 0;
	
	rtc_set(&current_time);
}

void app_run(void)
{
	#ifdef PC_BUILD
	pchal_tick();
	#endif //PC_BUILD

/*
	static uint32_t tc = 0;
	static uint8_t d = 0;
	if ( SDL_GetTicks() >= tc + 1000 )
	{
		tc = SDL_GetTicks();
		d++;
		if ( d > 9 ) d = 0;
	};
	lk_set_4digits(0, 0, 0, d);
	
	
	*/
	rtc_get(&current_time);
	lk_set_4digits(current_time.hour_10, current_time.hour, current_time.minute_10, current_time.minute);
	
}
