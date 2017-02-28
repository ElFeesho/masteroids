#pragma once

#include <stdio.h>
#include "ogc/lwp_watchdog.h"

#include <vector>
#include <utility>
#include <functional>

#include <SFML/System.hpp>

using std::vector;
using std::pair;
using std::function;

/**
Father...
*/
class GameTime
{
public:
	static unsigned long getMillis()
	{
		return clockTime.getElapsedTime().asMilliseconds();
	}

	static void tick()
    {
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

	static sf::Clock clockTime;
};
