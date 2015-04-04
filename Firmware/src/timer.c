#include <stdint.h>
#include <stdlib.h>
#include "hal.h"
#include "timer.h"

#ifndef MAX_NUMBER_TIMER
#error MAX_NUMBER_TIMER not defined!
#endif

struct timer_object
{
	uint16_t value;
	void (*callback)(void);
};
static struct timer_object timer_objects[MAX_NUMBER_TIMER+1];

void timer_init(void)
{
	for (uint8_t i = 0; i <= MAX_NUMBER_TIMER; i++)
	{
		timer_objects[i].value = 0;
		timer_objects[i].callback = NULL;
	};
	hal_timer_init(&timer_tick);
}

void timer_tick(void)
{
	for (uint8_t i = 0; i <= MAX_NUMBER_TIMER; i++)
	{
		if ( timer_objects[i].value > 0 ) timer_objects[i].value--;
			else if ( timer_objects[i].callback != NULL ) timer_objects[i].callback();
	};
}

timer_object_t timer_get_object(uint8_t number)
{
	return ( number <= MAX_NUMBER_TIMER ) ? &timer_objects[number] : NULL;
}

void timer_set_callback(timer_object_t self, void (*callback)(void))
{
	if ( self != NULL ) self->callback = callback;
}

void timer_set(timer_object_t self, uint16_t value)
{
	if ( self != NULL ) self->value = value;
}

uint16_t timer_get(timer_object_t self)
{
	return ( self != NULL ) ? self->value : 0;
}
