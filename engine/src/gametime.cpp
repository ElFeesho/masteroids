#include "gametime.h"

void GameTime::setTimeProvider(timeprovider timeProvider) {
	_timeProvider = timeProvider;
}

unsigned long GameTime::getMillis()
{
	return _timeProvider();
}

void GameTime::tick()
{
	lastDelta = getMillis() - lastTick;
	lastTick = getMillis();
	
	for (int i = pendingEvents.size() - 1; i >= 0; i--)
	{
		if (pendingEvents.at(i).first < lastTick)
		{
			pendingEvents.at(i).second();
			pendingEvents.erase(pendingEvents.begin() + i);
		}
	}
}

double GameTime::factorTime(double input)
{
	return input * timeMultiplier();
}

void GameTime::schedule(long delay, function<void()> event)
{
	pendingEvents.push_back(pair<long, function<void()>>(lastTick + delay, event));
}

double GameTime::timeMultiplier()
{
	return (double) lastDelta / 20.0f;
}

long GameTime::lastTick = 0;
long GameTime::lastDelta = 0;
vector<pair<long, function<void()>>> GameTime::pendingEvents;
GameTime::timeprovider GameTime::_timeProvider = []() { return 0; };