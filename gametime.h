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

class GameTime
{
	using eventFunc = function<void()>;
	using eventTuple = pair<long, eventFunc>;
public:
	static unsigned long getMillis()
	{
		return (unsigned long) clockTime.getElapsedTime().asMilliseconds();
	}

	static void tick()
    {
		lastDelta = getMillis() - lastTick;
		lastTick = getMillis();

		vector<eventTuple> executeList;
		std::remove_copy_if(pendingEvents.begin(), pendingEvents.end(), std::back_inserter(executeList), [](eventTuple event)
		{
			return event.first < lastTick;
		});

		std::for_each(executeList.begin(), executeList.end(), [](eventTuple event){
			event.second();
		});
	}

	static double factorTime(double input)
	{
		return input * timeMultiplier();
	}

	static void schedule(long delay, eventFunc event)
	{
		pendingEvents.push_back(eventTuple(lastTick + delay, event));
	}

private:

	static double timeMultiplier()
	{
		return (double) lastDelta / 20.0f;
	}

	static vector<eventTuple> pendingEvents;

	static long lastTick;
	static long lastDelta;

	static sf::Clock clockTime;
};
