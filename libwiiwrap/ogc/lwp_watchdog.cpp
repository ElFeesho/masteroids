#include "lwp_watchdog.h"

#include <SDL/SDL.h>

long gettime()
{
	return SDL_GetTicks();
}

long ticks_to_millisecs(long ticks)
{
	return ticks;
}