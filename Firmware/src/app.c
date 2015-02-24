#include <stdint.h>
#include "app.h"
#include "hal.h"
#include "lk.h"

#include <util/delay.h>
void app_init (void)
{
	hal_init ();
	lk_init ();
}

void app_run (void)
{
	//hal_led_number_set (1);
	//hal_led_set (DIGIT_E);
	lk_set_4digits (0, 1, 2, 3);
}