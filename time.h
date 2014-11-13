#ifndef __TIME_H__
#define __TIME_H__
#include <cstdio>
#include <ogc/lwp_watchdog.h>

/**
Father...
*/
class Time
{
public:
	static long getMillis()
	{
		return ticks_to_millisecs(gettime());
	}

	static void tick()
	{
		long prevTick = lastTick;
		lastDelta = getMillis() - lastTick;
		lastTick = getMillis();
	}

	static double factorTime(double input)
	{
		return input * timeMultiplier();
	}
private:

	static double timeMultiplier()
	{
		return (double)lastDelta/50.0f;
	}

	static long lastTick;
	static long lastDelta;
};

#endif
