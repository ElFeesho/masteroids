#include "lwp_watchdog.h"

#include <SFML/System.hpp>

static sf::Clock clockTime;

long gettime()
{
    return clockTime.getElapsedTime().asMilliseconds();
}

long ticks_to_millisecs(long ticks)
{
	return ticks;
}
