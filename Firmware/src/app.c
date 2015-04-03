#include <stdint.h>
#include <stdlib.h>
#include "hal.h"
#include "timer.h"
#include "lk.h"
#include "rtc.h"

rtc_time_t current_time = {0, 0, 0, 0, 0, 0};
rtc_time_t alarm_time = {0, 0, 0, 0, 0, 0};
//static void time_hour

// FSM 
enum fsm_signals {NONE = 0, MODE, MODE_FIX, MODE_A, MODE_A_FIX, UP, DOWN, ALARM_ON, ALARM_OFF, LIST_ON, LIST_OFF};
static enum fsm_signals fsm_get_signal(void);
enum fsm_states {NORMAL = 0, MIN, HOUR, MIN_A, HOUR_A, ALARM, LIST};
typedef void (*fsm_callback)(enum fsm_states state, enum fsm_signals signal);

static void fsm_worker_set_normal(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_normal(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_set_mode(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_set_mode_a(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_change_time(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_change_time_min(rtc_time_t* time, enum fsm_signals signal);
static void fsm_worker_change_time_hour(rtc_time_t* time, enum fsm_signals signal);

struct fsm_rec
{
	enum fsm_states new_state;
	fsm_callback worker;
};
static struct fsm_rec fsm[7][11] = 
{
	[NORMAL][NONE] = {NORMAL, &fsm_worker_normal},
	[NORMAL][MODE] = {MIN, &fsm_worker_set_mode},
	[NORMAL][MODE_FIX] = {NORMAL, NULL},
	[NORMAL][MODE_A] = {MIN_A, &fsm_worker_set_mode_a},
	[NORMAL][MODE_A_FIX] = {NORMAL, NULL},
	[NORMAL][UP] = {NORMAL, NULL},
	[NORMAL][DOWN] = {NORMAL, NULL},
	[NORMAL][ALARM_ON] = {ALARM, NULL},
	[NORMAL][ALARM_OFF] = {NORMAL, NULL},
	[NORMAL][LIST_ON] = {LIST, NULL},
	[NORMAL][LIST_OFF] = {NORMAL, NULL},
	[MIN][NONE] = {MIN, &fsm_worker_normal},
	[MIN][MODE] = {HOUR, &fsm_worker_set_mode},
	[MIN][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[MIN][MODE_A] = {MIN, NULL},
	[MIN][MODE_A_FIX] = {MIN, NULL},
	[MIN][UP] = {MIN, &fsm_worker_change_time},
	[MIN][DOWN] = {MIN, &fsm_worker_change_time},
	[MIN][ALARM_ON] = {ALARM, NULL},
	[MIN][ALARM_OFF] = {MIN, NULL},
	[MIN][LIST_ON] = {LIST, NULL},
	[MIN][LIST_OFF] = {NORMAL, &fsm_worker_set_normal},
	[HOUR][NONE] = {HOUR, &fsm_worker_normal},
	[HOUR][MODE] = {MIN, &fsm_worker_set_mode},
	[HOUR][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[HOUR][MODE_A] = {HOUR, NULL},
	[HOUR][MODE_A_FIX] = {HOUR, NULL},
	[HOUR][UP] = {HOUR, &fsm_worker_change_time},
	[HOUR][DOWN] = {HOUR, &fsm_worker_change_time},
	[HOUR][ALARM_ON] = {ALARM, NULL},
	[HOUR][ALARM_OFF] = {HOUR, NULL},
	[HOUR][LIST_ON] = {LIST, NULL},
	[HOUR][LIST_OFF] = {NORMAL, &fsm_worker_set_normal},
	[MIN_A][NONE] = {MIN_A, NULL},
	[MIN_A][MODE] = {MIN_A, NULL},
	[MIN_A][MODE_FIX] = {MIN_A, NULL},
	[MIN_A][MODE_A] = {HOUR_A, &fsm_worker_set_mode_a},
	[MIN_A][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[MIN_A][UP] = {MIN_A, &fsm_worker_change_time},
	[MIN_A][DOWN] = {MIN_A, &fsm_worker_change_time},
	[MIN_A][ALARM_ON] = {ALARM, NULL},
	[MIN_A][ALARM_OFF] = {MIN_A, NULL},
	[MIN_A][LIST_ON] = {LIST, NULL},
	[MIN_A][LIST_OFF] = {NORMAL, &fsm_worker_set_normal},
	[HOUR_A][NONE] = {HOUR_A, NULL},
	[HOUR_A][MODE] = {HOUR_A, NULL},
	[HOUR_A][MODE_FIX] = {HOUR_A, NULL},
	[HOUR_A][MODE_A] = {MIN_A, &fsm_worker_set_mode_a},
	[HOUR_A][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[HOUR_A][UP] = {HOUR_A, &fsm_worker_change_time},
	[HOUR_A][DOWN] = {HOUR_A, &fsm_worker_change_time},
	[HOUR_A][ALARM_ON] = {ALARM, NULL},
	[HOUR_A][ALARM_OFF] = {HOUR_A, NULL},
	[HOUR_A][LIST_ON] = {LIST, NULL},
	[HOUR_A][LIST_OFF] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][NONE] = {ALARM, NULL},
	[ALARM][MODE] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][MODE_A] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][UP] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][DOWN] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][ALARM_ON] = {ALARM, NULL},
	[ALARM][ALARM_OFF] = {NORMAL, &fsm_worker_set_normal},
	[ALARM][LIST_ON] = {ALARM, NULL},
	[ALARM][LIST_OFF] = {ALARM, NULL},
	[LIST][NONE] = {LIST, NULL},
	[LIST][MODE] = {NORMAL, &fsm_worker_set_normal},
	[LIST][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[LIST][MODE_A] = {NORMAL, &fsm_worker_set_normal},
	[LIST][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[LIST][UP] = {NORMAL, &fsm_worker_set_normal},
	[LIST][DOWN] = {NORMAL, &fsm_worker_set_normal},
	[LIST][ALARM_ON] = {ALARM, NULL},
	[LIST][ALARM_OFF] = {LIST, NULL},
	[LIST][LIST_ON] = {LIST, NULL},
	[LIST][LIST_OFF] = {NORMAL, &fsm_worker_set_normal}
};

void app_init(void)
{
	hal_init();
	timer_init();
	lk_init();
	rtc_init();
	rtc_get(&current_time);
	rtc_get_alarm(&alarm_time);
	//fsm_worker_set_normal(NORMAL, NONE);
}

void app_run(void)
{
	#ifdef PC_BUILD
	pchal_tick();
	#endif //PC_BUILD
	//FSM
	static enum fsm_states fsm_state = NORMAL;
	enum fsm_signals fsm_signal = fsm_get_signal();
	if ( fsm[fsm_state][fsm_signal].worker != NULL ) fsm[fsm_state][fsm_signal].worker(fsm_state, fsm_signal);
	fsm_state = fsm[fsm_state][fsm_signal].new_state;
	//Common code
	if ( current_time.second & 0x01 ) lk_set_ddot(LK_LED_ON); else lk_set_ddot(LK_LED_OFF);
	//rtc_get(&current_time);
	//if ( fsm_state == NORMAL )  lk_set_aled(2, LK_LED_ON); else lk_set_aled(2, LK_LED_OFF);
	if ( fsm_state == MIN )  lk_set_aled(0, LK_LED_ON); else lk_set_aled(0, LK_LED_OFF);
	if ( fsm_state == HOUR )  lk_set_aled(1, LK_LED_ON); else lk_set_aled(1, LK_LED_OFF);
}

static enum fsm_signals fsm_get_signal(void)
{
	enum fsm_signals signal = NONE;
	static uint8_t keys[MAX_NUMBER_DIGIT + 1] = {0, 0, 0, 0, 0};
	for (uint8_t i = 0; i <= MAX_NUMBER_DIGIT; i++)
	{
		if ( lk_get_key(i) == 0 )
		{
			keys[i] = 0;
		}
		else if ( keys[i] == 0 )
		{
			keys[i] = 1;
			//start timer
			if ( i != LK_KEY_ALARM_ENABLE ) timer_set(timer_get_object(TIMER_APP_KEY_0 + i), LK_KEY_FIX);
			switch (i)
			{
				case LK_KEY_UP:
					signal = UP; break;
				case LK_KEY_DOWN:
					signal = DOWN; break;
				case LK_KEY_CLOCK_SET:
					signal = MODE; break;
				case LK_KEY_ALARM_SET:
					signal = MODE_A; break;
				case LK_KEY_ALARM_ENABLE:
					signal = ALARM_OFF;
					break;
				default:
					signal = NONE;
			};
		}
		else if ( timer_get(timer_get_object(TIMER_APP_KEY_0 + i)) == 0 )
		{
			if ( i != LK_KEY_ALARM_ENABLE ) timer_set(timer_get_object(TIMER_APP_KEY_0 + i), LK_KEY_REPEAT);
			switch (i)
			{
				case LK_KEY_UP:
					signal = UP; break;
				case LK_KEY_DOWN:
					signal = DOWN; break;
				case LK_KEY_CLOCK_SET:
					signal = MODE_FIX; break;
				case LK_KEY_ALARM_SET:
					signal = MODE_A_FIX; break;
				default:
					signal = NONE;
			};

		};
	};
	return signal;
}

static void fsm_worker_set_normal(enum fsm_states state, enum fsm_signals signal)
{
	lk_set_digit_state(0, LK_LED_ON); lk_set_digit_state(1, LK_LED_ON); lk_set_digit_state(2, LK_LED_ON); lk_set_digit_state(3, LK_LED_ON);
	lk_set_alarm(LK_LED_OFF);
	lk_set_aled(2, LK_LED_OFF); //Индикация настройки будильника
}

static void fsm_worker_normal(enum fsm_states state, enum fsm_signals signal)
{
	rtc_get(&current_time);
	lk_set_4digits(current_time.hour_10, current_time.hour, current_time.minute_10, current_time.minute);
}

static void fsm_worker_set_mode(enum fsm_states state, enum fsm_signals signal)
{
	switch (state)
	{
		case HOUR:
		case HOUR_A:
		case NORMAL:
			lk_set_digit_state(0, LK_LED_ON);
			lk_set_digit_state(1, LK_LED_ON);
			lk_set_digit_state(2, LK_LED_BLINK);
			lk_set_digit_state(3, LK_LED_BLINK);
			break;
		case MIN:
		case MIN_A:
			lk_set_digit_state(0, LK_LED_BLINK);
			lk_set_digit_state(1, LK_LED_BLINK);
			lk_set_digit_state(2, LK_LED_ON);
			lk_set_digit_state(3, LK_LED_ON);
		default:
			return;
	};
}

static void fsm_worker_set_mode_a(enum fsm_states state, enum fsm_signals signal)
{
	lk_set_aled(2, LK_LED_BLINK);
	lk_set_4digits(alarm_time.hour_10, alarm_time.hour, alarm_time.minute_10, alarm_time.minute);
	fsm_worker_set_mode(state, signal);
}

static void fsm_worker_change_time(enum fsm_states state, enum fsm_signals signal)
{
	rtc_time_t* time;
	void (*set_time)(const rtc_time_t* time);
	if ( state == MIN || state == HOUR )
	{
		time = &current_time;
		set_time = &rtc_set;
	}
	else if ( state == MIN_A || state == HOUR_A )
	{
		time = &alarm_time;
		set_time = &rtc_set_alarm;
	} else return;
	
	if ( state == MIN || state == MIN_A ) fsm_worker_change_time_min(time, signal);
	else if ( state == HOUR || state == HOUR_A ) fsm_worker_change_time_hour(time, signal);
	time->second_10 = 0; time->second_10 = 0;
	set_time(time);
	lk_set_4digits(time->hour_10, time->hour, time->minute_10, time->minute);
}

static void fsm_worker_change_time_min(rtc_time_t* time, enum fsm_signals signal)
{
	if ( signal == UP )
	{
		time->minute++;
		if ( time->minute >= 10 ) { time->minute = 0; time->minute_10++; };
		if ( time->minute_10 >= 6 ) { time->minute = 0; time->minute_10 = 0; fsm_worker_change_time_hour(time, UP); };
	} else if ( signal == DOWN )
	{
		time->minute--;
		if ( time->minute < 0 ) { time->minute = 9; time->minute_10--; };
		if ( time->minute_10 < 0 ) { time->minute_10 = 5; fsm_worker_change_time_hour(time, DOWN); };
	};
}

static void fsm_worker_change_time_hour(rtc_time_t* time, enum fsm_signals signal)
{
	if ( signal == UP )
	{
		time->hour++;
		if ( time->hour >= 10 ) { time->hour = 0; time->hour_10++; };
		if ( time->hour_10 >= 2 && time->hour >= 4 ) { time->hour = 0; time->hour_10 = 0; };
	} else if ( signal == DOWN )
	{
		time->hour--;
		if ( time->hour < 0 ) { time->hour = 9; time->hour_10--; };
		if ( time->hour_10 < 0 ) { time->hour = 3; time->hour_10 = 2; };
	};
}
