#ifndef TIMER_H
#define TIMER_H

struct timer_object;
typedef struct timer_object* timer_object_t;

void timer_init(void);
void timer_tick(void);
timer_object_t timer_get_object(uint8_t number);

void timer_set_callback(timer_object_t self, void (*callback)(void));
void timer_set(timer_object_t self, uint16_t value);
uint16_t timer_get(timer_object_t self);

/*
void timer_init(void);
void timer_getobject

void timer_set
void timer_get
*/
#endif //TIMER_H