#ifndef __TIME_H__
#define __TIME_H__

#include <stdio.h>
#include "ogc/lwp_watchdog.h"

#include <vector>
#include <utility>
#include <functional>

using std::vector;
using std::pair;
using std::function;

/**
Father...
*/
class GameTime
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
		// Run through events
		for (int i = pendingEvents.size() - 1; i >= 0; i--)
		{
			if (pendingEvents.at(i).first < lastTick)
			{
				pendingEvents.at(i).second();
				pendingEvents.erase(pendingEvents.begin() + i);
			}
		}

	}

	static double factorTime(double input)
	{
		return input * timeMultiplier();
	}

	static void schedule(long delay, function<void()> event)
	{
		pendingEvents.push_back(pair<long, function<void()>>(lastTick + delay, event));
	}

private:

	static double timeMultiplier()
	{
		return (double) lastDelta / 20.0f;
	}

	static vector<pair<long, function<void()>>> pendingEvents;

	static long lastTick;
	static long lastDelta;
};

#endif
