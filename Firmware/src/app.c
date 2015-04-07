#include <stdint.h>
#include <stdlib.h>
#include "hal.h"
#include "timer.h"
#include "lk.h"
#include "rtc.h"
#include "random.h"

static rtc_time_t current_time = {0, 0, 0, 0, 0, 0};
static rtc_time_t alarm_time = {0, 0, 0, 0, 0, 0};
static rtc_time_t list_time = {0, 0, 0, 0, 0, 0};

typedef struct
{
	uint8_t enable;
	uint8_t work;
	uint8_t end;
	uint8_t i;
} state_t;
static state_t alarm_state = {.enable = 0, .work = 0, .end = 1, .i = 0};
static state_t list_state = {.enable = 0, .work = 0, .end = 1, .i = 0};

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
static void fsm_worker_alarm(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_set_alarm(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_list(enum fsm_states state, enum fsm_signals signal);
static void fsm_worker_set_list(enum fsm_states state, enum fsm_signals signal);

typedef struct
{
	enum fsm_states new_state;
	fsm_callback worker;
} fsm_t;
static fsm_t fsm[7][11] = 
{
	[NORMAL][NONE] = {NORMAL, &fsm_worker_normal},
	[NORMAL][MODE] = {MIN, &fsm_worker_set_mode},
	[NORMAL][MODE_FIX] = {NORMAL, NULL},
	[NORMAL][MODE_A] = {MIN_A, &fsm_worker_set_mode_a},
	[NORMAL][MODE_A_FIX] = {NORMAL, NULL},
	[NORMAL][UP] = {NORMAL, NULL},
	[NORMAL][DOWN] = {NORMAL, NULL},
	[NORMAL][ALARM_ON] = {ALARM, &fsm_worker_set_alarm},
	[NORMAL][ALARM_OFF] = {NORMAL, NULL},
	[NORMAL][LIST_ON] = {LIST, &fsm_worker_set_list},
	[NORMAL][LIST_OFF] = {NORMAL, NULL},
	[MIN][NONE] = {MIN, &fsm_worker_normal},
	[MIN][MODE] = {HOUR, &fsm_worker_set_mode},
	[MIN][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[MIN][MODE_A] = {MIN, NULL},
	[MIN][MODE_A_FIX] = {MIN, NULL},
	[MIN][UP] = {MIN, &fsm_worker_change_time},
	[MIN][DOWN] = {MIN, &fsm_worker_change_time},
	[MIN][ALARM_ON] = {ALARM, &fsm_worker_set_alarm},
	[MIN][ALARM_OFF] = {MIN, NULL},
	[MIN][LIST_ON] = {LIST, &fsm_worker_set_list},
	[MIN][LIST_OFF] = {MIN, NULL},
	[HOUR][NONE] = {HOUR, &fsm_worker_normal},
	[HOUR][MODE] = {MIN, &fsm_worker_set_mode},
	[HOUR][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[HOUR][MODE_A] = {HOUR, NULL},
	[HOUR][MODE_A_FIX] = {HOUR, NULL},
	[HOUR][UP] = {HOUR, &fsm_worker_change_time},
	[HOUR][DOWN] = {HOUR, &fsm_worker_change_time},
	[HOUR][ALARM_ON] = {ALARM, &fsm_worker_set_alarm},
	[HOUR][ALARM_OFF] = {HOUR, NULL},
	[HOUR][LIST_ON] = {LIST, &fsm_worker_set_list},
	[HOUR][LIST_OFF] = {HOUR, NULL},
	[MIN_A][NONE] = {MIN_A, NULL},
	[MIN_A][MODE] = {MIN_A, NULL},
	[MIN_A][MODE_FIX] = {MIN_A, NULL},
	[MIN_A][MODE_A] = {HOUR_A, &fsm_worker_set_mode_a},
	[MIN_A][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[MIN_A][UP] = {MIN_A, &fsm_worker_change_time},
	[MIN_A][DOWN] = {MIN_A, &fsm_worker_change_time},
	[MIN_A][ALARM_ON] = {ALARM, &fsm_worker_set_alarm},
	[MIN_A][ALARM_OFF] = {MIN_A, NULL},
	[MIN_A][LIST_ON] = {LIST, &fsm_worker_set_list},
	[MIN_A][LIST_OFF] = {MIN_A, NULL},
	[HOUR_A][NONE] = {HOUR_A, NULL},
	[HOUR_A][MODE] = {HOUR_A, NULL},
	[HOUR_A][MODE_FIX] = {HOUR_A, NULL},
	[HOUR_A][MODE_A] = {MIN_A, &fsm_worker_set_mode_a},
	[HOUR_A][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[HOUR_A][UP] = {HOUR_A, &fsm_worker_change_time},
	[HOUR_A][DOWN] = {HOUR_A, &fsm_worker_change_time},
	[HOUR_A][ALARM_ON] = {ALARM, &fsm_worker_set_alarm},
	[HOUR_A][ALARM_OFF] = {HOUR_A, NULL},
	[HOUR_A][LIST_ON] = {LIST, &fsm_worker_set_list},
	[HOUR_A][LIST_OFF] = {HOUR_A, NULL},
	[ALARM][NONE] = {ALARM, &fsm_worker_alarm},
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
	[LIST][NONE] = {LIST, &fsm_worker_list},
	[LIST][MODE] = {NORMAL, &fsm_worker_set_normal},
	[LIST][MODE_FIX] = {NORMAL, &fsm_worker_set_normal},
	[LIST][MODE_A] = {NORMAL, &fsm_worker_set_normal},
	[LIST][MODE_A_FIX] = {NORMAL, &fsm_worker_set_normal},
	[LIST][UP] = {NORMAL, &fsm_worker_set_normal},
	[LIST][DOWN] = {NORMAL, &fsm_worker_set_normal},
	[LIST][ALARM_ON] = {ALARM, &fsm_worker_set_alarm},
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
	alarm_state.enable = rtc_get_alarm_state();
	rtc_get(&list_time);
}

void app_run(void)
{
	static uint8_t i = 0;
	#ifdef PC_BUILD
	pchal_tick();
	#endif //PC_BUILD
	//FSM
	static enum fsm_states fsm_state = NORMAL;
	enum fsm_signals fsm_signal = fsm_get_signal();
	//Auto set NORMAL
	if ( fsm_signal != NONE ) i = 0;
		else if ( timer_get(timer_get_object(TIMER_APP_AUTO_NORMAL)) == 0 )
		{
			i++;
			timer_set(timer_get_object(TIMER_APP_AUTO_NORMAL), 1000);
		};
	if ( i >= 42 )
	{
		fsm_state = NORMAL;
		fsm_worker_set_normal(NORMAL, NONE);
		i = 0;
	};
	if ( fsm[fsm_state][fsm_signal].worker != NULL ) fsm[fsm_state][fsm_signal].worker(fsm_state, fsm_signal);
	fsm_state = fsm[fsm_state][fsm_signal].new_state;
	//Common code
	rtc_get(&current_time);
	if ( fsm_state != MIN_A && fsm_state != HOUR_A )
	{
		if ( alarm_state.enable == 0 ) lk_set_aled(3, LK_LED_OFF); else lk_set_aled(3, LK_LED_ON);
	};
}

static enum fsm_signals fsm_get_signal(void)
{
	enum fsm_signals signal = NONE;
	static uint8_t keys[MAX_NUMBER_DIGIT + 1] = {0, 0, 0, 0, 0};
	
	if ( alarm_time.hour_10 == current_time.hour_10 && alarm_time.hour == current_time.hour &&
		alarm_time.minute_10 == current_time.minute_10 && alarm_time.minute == current_time.minute &&
		alarm_time.second_10 == current_time.second_10 && alarm_time.second == current_time.second &&
		alarm_state.enable == 1 && alarm_state.work == 0 ) return ALARM_ON;
	if ( alarm_state.end == 1 && alarm_state.work == 1 ) return ALARM_OFF;

	if ( list_time.hour_10 == current_time.hour_10 && list_time.hour == current_time.hour &&
		list_time.minute_10 == current_time.minute_10 && list_time.minute <= current_time.minute &&
		list_time.second_10 <= current_time.second_10 && list_time.second <= current_time.second &&
		list_state.work == 0 ) return LIST_ON;
	if ( list_state.end == 1 && list_state.work == 1 ) return LIST_OFF;
	
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
					if ( !alarm_state.work )
					{
						if ( alarm_state.enable == 0 ) alarm_state.enable = 1; else alarm_state.enable = 0;
						rtc_set_alarm_state(alarm_state.enable);
					};
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
	alarm_state.work = 0;
	list_state.work = 0;
}

static void fsm_worker_normal(enum fsm_states state, enum fsm_signals signal)
{
	lk_set_4digits(current_time.hour_10, current_time.hour, current_time.minute_10, current_time.minute);
	if ( current_time.second & 0x01 ) lk_set_ddot(LK_LED_ON); else lk_set_ddot(LK_LED_OFF);
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
	lk_set_aled(3, LK_LED_BLINK);
	lk_set_ddot(LK_LED_OFF);
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
	}
	else if ( signal == DOWN )
	{
		if ( time->minute != 0 )
		{
			time->minute--;
		}
		else
		{
			time->minute = 9;
			if ( time->minute_10 != 0 )
			{
				time->minute_10--;
			}
			else
			{
				time->minute_10 = 5;
				fsm_worker_change_time_hour(time, DOWN);
			};
		};
	};
}

static void fsm_worker_change_time_hour(rtc_time_t* time, enum fsm_signals signal)
{
	if ( signal == UP )
	{
		time->hour++;
		if ( time->hour >= 10 ) { time->hour = 0; time->hour_10++; };
		if ( time->hour_10 >= 2 && time->hour >= 4 ) { time->hour = 0; time->hour_10 = 0; };
	}
	else if ( signal == DOWN )
	{
		if ( time->hour != 0 )
		{
			time->hour--;
		}
		else
		{
			time->hour = 9;
			if ( time->hour_10 != 0 )
			{
				time->hour_10--;
			}
			else
			{
				time->hour = 3;
				time->hour_10 = 2;
			};
		};
	};
}

static void fsm_worker_alarm(enum fsm_states state, enum fsm_signals signal)
{
	if ( timer_get(timer_get_object(TIMER_APP_ALARM)) == 0 && alarm_state.i <= 6 )
	{
		if ( (alarm_state.i & 1) == 0 )
		{
			timer_set(timer_get_object(TIMER_APP_ALARM), 150);
			lk_set_alarm(LK_LED_ON);
		}
		else
		{
			timer_set(timer_get_object(TIMER_APP_ALARM), 1000);
			lk_set_alarm(LK_LED_OFF);
		};
		alarm_state.i++;
	};
	if ( alarm_state.i > 6 ) lk_set_alarm(LK_LED_ON);
	if ( current_time.hour_10 == alarm_time.hour_10 && current_time.hour == alarm_time.hour &&
		current_time.minute_10 == alarm_time.minute_10 && current_time.minute == alarm_time.minute &&
		current_time.second_10 >= alarm_time.second_10 + 3 && current_time.second >= alarm_time.second ) alarm_state.end = 1;
	fsm_worker_normal(state, signal);
}

static void fsm_worker_set_alarm(enum fsm_states state, enum fsm_signals signal)
{
	lk_set_alarm(LK_LED_ON);
	fsm_worker_set_normal(state, signal);
	alarm_state.end = 0; alarm_state.work = 1; alarm_state.i = 0;
}

static void fsm_worker_list(enum fsm_states state, enum fsm_signals signal)
{
	static uint8_t d0, d1, d2, d3;
	if ( timer_get(timer_get_object(TIMER_APP_LIST)) == 0 )
	{
		timer_set(timer_get_object(TIMER_APP_LIST), 100);
		if ( d0 < 9 )
		{
			d0++; list_time.minute++;
			if ( list_time.minute > 9 ) list_time.minute = 0;
		};
		if ( d1 < 9 && d0 > 4 )
		{
			d1++; list_time.minute_10++;
			if ( list_time.minute_10 > 9 ) list_time.minute_10 = 0;
		};
		if ( d2 < 9 && d1 > 4 )
		{
			d2++; list_time.hour++;
			if ( list_time.hour > 9 ) list_time.hour = 0;
		};
		if ( d3 < 9 && d2 > 4 )
		{
			d3++; list_time.hour_10++;
			if ( list_time.hour_10 > 9 ) list_time.hour_10 = 0;
		};
		lk_set_4digits(list_time.hour_10, list_time.hour, list_time.minute_10, list_time.minute);
		if ( d0 >= 9 && d1 >= 9 && d2 >= 9 && d3 >= 9 )
		{
			list_state.end = 1;
			d0 = d1 = d2 = d3 = 0;
			rtc_get(&list_time);
			fsm_worker_change_time_hour(&list_time, UP);
			list_time.minute_10 = random_ubyte_in(0, 5);
			list_time.minute = random_ubyte_in(0, 9);
		};
	};
}

static void fsm_worker_set_list(enum fsm_states state, enum fsm_signals signal)
{
	fsm_worker_set_normal(state, signal);
	list_state.end = 0; list_state.work = 1; list_state.i = 0;
	list_time.hour_10 = current_time.hour_10; list_time.hour = current_time.hour;
	list_time.minute_10 = current_time.minute_10; list_time.minute = current_time.minute;
}
