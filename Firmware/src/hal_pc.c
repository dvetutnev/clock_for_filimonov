#include <stdint.h>

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "hal.h"

static int16_t pchal_init(void);
static int16_t pchal_set_segment(char segment, uint8_t state, int16_t offset_x, int16_t offset_y);
static void pchal_getoffset(uint8_t number, int16_t *offset_x, int16_t *offset_y);
//static uint32_t pchal_tick(uint32_t interval, void *param);

// PC emulation
static SDL_Window *window;
static SDL_Renderer *renderer;

static uint8_t number_digit = 0;
static uint8_t alarm_state = 0;
static uint8_t digits[MAX_NUMBER_DIGIT + 1];
static void (*timer_callback)(void) = NULL;

// Interface
void hal_init(void)
{
	uint8_t i;
	if ( pchal_init() != 0 ) exit(1);
	for ( i = 0; i <= MAX_NUMBER_DIGIT; i++ ) digits[i] = 0;
}

void hal_timer_init(void (*callback)(void))
{
	timer_callback = callback;
	return;
}
void hal_led_off(void)
{
	return;
	int16_t offset_x, offset_y;
	pchal_getoffset (number_digit, &offset_x, &offset_y);
	if ( number_digit == NUMBER_NOT_DIGIT ) return;
	if ( (digits[number_digit] & SEGMENT_A) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_A;
		pchal_set_segment('a', 0, offset_x, offset_y);
	};
	if ( (digits[number_digit] & SEGMENT_B) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_B;
		pchal_set_segment('b', 0, offset_x, offset_y);
	};
	if ( (digits[number_digit] & SEGMENT_C) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_C;
		pchal_set_segment('c', 0, offset_x, offset_y);
	};
	if ( (digits[number_digit] & SEGMENT_D) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_D;
		pchal_set_segment('d', 0, offset_x, offset_y);
	};
	if ( (digits[number_digit] & SEGMENT_E) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_E;
		pchal_set_segment('e', 0, offset_x, offset_y);
	};
	if ( (digits[number_digit] & SEGMENT_F) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_F;
		pchal_set_segment('f', 0, offset_x, offset_y);
	};
	if ( (digits[number_digit] & SEGMENT_G) != 0 )
	{
		digits[number_digit] &= ~SEGMENT_G;
		pchal_set_segment('g', 0, offset_x, offset_y);
	};
}

void hal_led_set(uint8_t value)
{
	int16_t offset_x, offset_y;
	pchal_getoffset (number_digit, &offset_x, &offset_y);
	if ( number_digit == NUMBER_NOT_DIGIT )
	{
	if ( (value & SEGMENT_ADD_0) != (digits[number_digit] & SEGMENT_ADD_0) ) {
		if ( value & SEGMENT_ADD_0 )
		{
			digits[number_digit] |= SEGMENT_ADD_0;
			pchal_set_segment('0', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_ADD_0;
			pchal_set_segment('0', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_ADD_1) != (digits[number_digit] & SEGMENT_ADD_1) ) {
		if ( value & SEGMENT_ADD_1 )
		{
			digits[number_digit] |= SEGMENT_ADD_1;
			pchal_set_segment('1', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_ADD_1;
			pchal_set_segment('1', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_ADD_2) != (digits[number_digit] & SEGMENT_ADD_2) ) {
		if ( value & SEGMENT_ADD_2 )
		{
			digits[number_digit] |= SEGMENT_ADD_2;
			pchal_set_segment('2', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_ADD_2;
			pchal_set_segment('2', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_ADD_3) != (digits[number_digit] & SEGMENT_ADD_3) ) {
		if ( value & SEGMENT_ADD_3 )
		{
			digits[number_digit] |= SEGMENT_ADD_3;
			pchal_set_segment('3', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_ADD_3;
			pchal_set_segment('3', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_DOT_0) != (digits[number_digit] & SEGMENT_DOT_0) ) {
		if ( value & SEGMENT_DOT_0 )
		{
			digits[number_digit] |= SEGMENT_DOT_0;
			pchal_set_segment('4', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_DOT_0;
			pchal_set_segment('4', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_DOT_1) != (digits[number_digit] & SEGMENT_DOT_1) ) {
		if ( value & SEGMENT_DOT_1 )
		{
			digits[number_digit] |= SEGMENT_DOT_1;
			pchal_set_segment('5', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_DOT_1;
			pchal_set_segment('5', 0, offset_x, offset_y);
	}; };
		
		return;
	};
	
	if ( (value & SEGMENT_A) != (digits[number_digit] & SEGMENT_A) ) {
		if ( value & SEGMENT_A )
		{
			digits[number_digit] |= SEGMENT_A;
			pchal_set_segment('a', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_A;
			pchal_set_segment('a', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_B) != (digits[number_digit] & SEGMENT_B) ) {
		if ( value & SEGMENT_B )
		{
			digits[number_digit] |= SEGMENT_B;
			pchal_set_segment('b', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_B;
			pchal_set_segment('b', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_C) != (digits[number_digit] & SEGMENT_C) ) {
		if ( value & SEGMENT_C )
		{
			digits[number_digit] |= SEGMENT_C;
			pchal_set_segment('c', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_C;
			pchal_set_segment('c', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_D) != (digits[number_digit] & SEGMENT_D) ) {
		if ( value & SEGMENT_D )
		{
			digits[number_digit] |= SEGMENT_D;
			pchal_set_segment('d', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_D;
			pchal_set_segment('d', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_E) != (digits[number_digit] & SEGMENT_E) ) {
		if ( value & SEGMENT_E )
		{
			digits[number_digit] |= SEGMENT_E;
			pchal_set_segment('e', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_E;
			pchal_set_segment('e', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_F) != (digits[number_digit] & SEGMENT_F) ) {
		if ( value & SEGMENT_F )
		{
			digits[number_digit] |= SEGMENT_F;
			pchal_set_segment('f', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_F;
			pchal_set_segment('f', 0, offset_x, offset_y);
	}; };
	if ( (value & SEGMENT_G) != (digits[number_digit] & SEGMENT_G) ) {
		if ( value & SEGMENT_G )
		{
			digits[number_digit] |= SEGMENT_G;
			pchal_set_segment('g', 1, offset_x, offset_y);
		} else
		{
			digits[number_digit] &= ~SEGMENT_G;
			pchal_set_segment('g', 0, offset_x, offset_y);
	}; };

	return;
}

void hal_led_number_off(void)
{
	return;
}

void hal_led_number_set(uint8_t value)
{
	if ( value <= MAX_NUMBER_DIGIT ) number_digit = value;
	return;
}

void hal_alarm_set(uint8_t value)
{
	if ( value == alarm_state ) return;
	alarm_state = value;
	SDL_Rect segment_coordinates = {500, 50, 50, 50};
	if ( value )
	{
		// Clear segment
		SDL_RenderFillRect(renderer, &segment_coordinates);
		SDL_RenderPresent(renderer);
	} else
	{
		//Save color
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
		// Clear segment
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &segment_coordinates);
		SDL_RenderPresent(renderer);
		// Restore color
		SDL_SetRenderDrawColor (renderer, r, g, b, a);
	};
	return;
}

uint8_t hal_key_get(void);

// PC emulation
static int16_t pchal_init(void)
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) { printf("%s\t%s\n", "SDL_Init error!", SDL_GetError() ); return 1; };
	window = SDL_CreateWindow("clock_for_filimonov", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 300, SDL_WINDOW_SHOWN);
	if ( window == NULL ) { printf ("%s\t%s\n", "SDL_CreateWindow error!", SDL_GetError() ); return 1; };
	renderer = SDL_CreateRenderer(window, -1, 0);
	if ( renderer == NULL ) { printf ("%s\t%s\n", "SDL_CreateReneder error!", SDL_GetError() ); return 1; };
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	
	//SDL_AddTimer((33/10)*10, &pchal_tick, NULL);
	return 0;
}

static SDL_Rect pchal_segment_coordinates[] =
{
	//7segment
	{50, 10, 50, 10},
	{100, 20, 10, 70},
	{100, 100, 10, 70},
	{50, 170, 50, 10},
	{40, 100, 10, 70},
	{40, 20, 10, 70},
	{50, 90, 50, 10},
	//aled
	{10, 20, 20, 20},
	{10, 120, 20, 20},
	{460, 20, 20, 20},
	{460, 120, 20, 20},
	//ddot
	{235, 40, 20, 20},
	{235, 130, 20, 20}
};
static int16_t pchal_set_segment(char segment, uint8_t state, int16_t offset_x, int16_t offset_y)
{
	SDL_Rect segment_coordinates;
	// Load coordinates
	switch ( segment )
	{
		case 'a':
			segment_coordinates = pchal_segment_coordinates[0];
			break;
		case 'b':
			segment_coordinates = pchal_segment_coordinates[1];
			break;
		case 'c':
			segment_coordinates = pchal_segment_coordinates[2];
			break;
		case 'd':
			segment_coordinates = pchal_segment_coordinates[3];
			break;
		case 'e':
			segment_coordinates = pchal_segment_coordinates[4];
			break;
		case 'f':
			segment_coordinates = pchal_segment_coordinates[5];
			break;
		case 'g':
			segment_coordinates = pchal_segment_coordinates[6];
			break;
		case 'h':
			//segment_coordinates = pchal_segment_coordinates[0];
			return -1;
			break;
		case '0':
			segment_coordinates = pchal_segment_coordinates[7];
			break;
		case '1':
			segment_coordinates = pchal_segment_coordinates[8];
			break;
		case '2':
			segment_coordinates = pchal_segment_coordinates[9];
			break;
		case '3':
			segment_coordinates = pchal_segment_coordinates[10];
			break;
		case '4':
			segment_coordinates = pchal_segment_coordinates[11];
			break;
		case '5':
			segment_coordinates = pchal_segment_coordinates[12];
			break;
		default:
			return -1;
			break;
	};
	// Add offset
	segment_coordinates.x += offset_x;
	segment_coordinates.y += offset_y;
	if ( state == 0 || state == 1)
	{
		// Save color
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
		// Clear segment
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &segment_coordinates);
		SDL_RenderPresent(renderer);
		// Restore color
		SDL_SetRenderDrawColor (renderer, r, g, b, a);
	};
	switch ( state )
	{
		case 0:
			//SDL_RenderDrawRect (renderer, &segment_coordinates);
			break;
		case 1:
			SDL_RenderFillRect(renderer, &segment_coordinates);
			break;
		case 2:
			SDL_RenderDrawRect(renderer, &segment_coordinates);
			break;
		default:
			return -1;
			break;
	};
	SDL_RenderPresent(renderer);
	return 0;
} //static int16_t pchal_set_segment(char segment, uint8_t state, int16_t offset_x, int16_t offset_y)
int16_t pchal_set_segment_(char segment, uint8_t state, int16_t offset_x, int16_t offset_y)
{
	return pchal_set_segment(segment, state, offset_x, offset_y);
}

typedef struct
{
	uint16_t offset_x;
	uint16_t offset_y;
} digits_offset_t;
static digits_offset_t digits_offset[MAX_NUMBER_DIGIT + 1] =
{
	{0, 0},
	{90, 0},
	{250, 0},
	{340, 0},
	{0, 0}
};
static void pchal_getoffset(uint8_t number, int16_t *offset_x, int16_t *offset_y)
{
	if ( number == NUMBER_NOT_DIGIT )
	{
		*offset_x = 0;
		*offset_y = 0;
		return;
	};
	*offset_x = digits_offset[number].offset_x;
	*offset_y = digits_offset[number].offset_y;
	return;
}


//rtc
static uint8_t pchal_tc = 0;
static int32_t pchal_time_offset = 0;
void hal_iic_init(void)
{
	return;
}

void hal_iic_stop(void)
{
	return;
}

uint8_t hal_iic_start(uint8_t addr)
{
	pchal_tc = 0;
	return 0;
}

uint8_t hal_iic_rep_start(uint8_t addr)
{
	return 0;
}

void hal_iic_start_wait(uint8_t addr)
{
	return;
}

uint8_t hal_iic_write(uint8_t data)
{
	struct tm *tp;
	time_t t;
	int32_t offset;
	tp = NULL;
	t = time(NULL);
	tp = localtime(&t);
	offset = (data >> 4) * 10 + (data & 0xf);
	switch ( pchal_tc )
	{
		case 1:
			offset -= tp->tm_sec ;
			break;
		case 2:
			offset -= tp->tm_min;
			offset *= 60;
			break;
		case 3:
			offset -= tp->tm_hour;
			offset *= 3600;
			break;
		default : break;
	};
	pchal_time_offset += offset;
	pchal_tc++;
	return 0;
}

uint8_t hal_iic_read_ack(void)
{
	struct tm *tp;
	time_t t;
	uint8_t ret;
	tp = NULL;
	t = time(NULL) + pchal_time_offset;
	tp = localtime(&t);
	switch ( pchal_tc )
	{
		case 1:
			ret = ( (uint8_t)(tp->tm_sec / 10) << 4 ) | tp->tm_sec % 10;
			break;
		case 2:
			ret = ( (uint8_t)(tp->tm_min / 10) << 4 ) | tp->tm_min % 10;
			break;
		case 3:
			ret = ( (uint8_t)(tp->tm_hour / 10) << 4 ) | tp->tm_hour % 10;
			break;
		default : ret = 0;
	};
	pchal_tc++;
	return ret;
}

uint8_t hal_iic_read_nak(void)
{
	return hal_iic_read_ack();
}

//tick
//static uint32_t pchal_tick(uint32_t interval, void *param)
void pchal_tick(void)
{
	static uint32_t t = 0;
	uint32_t tc;
	tc = SDL_GetTicks();
	if ( t >= tc) return;
	t = tc;
	SDL_Event event;
	if ( timer_callback != NULL ) timer_callback();
	//printf("offset: %d\n", pchal_time_offset);
	while ( SDL_PollEvent(&event) )
	{
		//printf("SDL Event, SDL tick: %d\n", SDL_GetTicks());
		if ( event.type == SDL_QUIT )
		{
			SDL_Quit();
			exit(0);
		};
		if ( event.type == SDL_KEYDOWN)
		{
			printf("Keydown\n");
			//switch ( event.key.keysym.sym )
			
		};
	}
	//SDL_AddTimer((33/10)*10, &pchal_tick, NULL);
	return;
}
