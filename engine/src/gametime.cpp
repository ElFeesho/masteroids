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

	for (auto scheduledEvent : _scheduledRepetitions)
	{
		RepeatToken token = scheduledEvent.first;
		unsigned long frequency = scheduledEvent.second.first;
		unsigned long lastExecution = _repeatExecutionTimes[token];

		if (lastExecution+frequency < lastTick)
		{
			scheduledEvent.second.second();
			_repeatExecutionTimes[token] = lastTick;
		}
	}
}

double GameTime::factorTime(double input)
{
	return input * timeMultiplier();
}

void GameTime::schedule(unsigned long delay, function<void()> event)
{
	pendingEvents.push_back(pair<unsigned long, function<void()>>(lastTick + delay, event));
}

double GameTime::timeMultiplier()
{
	return (double) lastDelta / 20.0f;
}

GameTime::RepeatToken GameTime::scheduleRepeating(unsigned long interval, function<void()> event) {
	RepeatToken token = _repeatExecutionTimes.size();
	_repeatExecutionTimes[token] = getMillis();
	_scheduledRepetitions[token] = pair<unsigned long, function<void()>>(interval, event);
	return token;
}

void GameTime::removeRepeating(GameTime::RepeatToken eventToken) {
	_repeatExecutionTimes.erase(_repeatExecutionTimes.find(eventToken));
	_scheduledRepetitions.erase(_scheduledRepetitions.find(eventToken));
}

unsigned long GameTime::lastTick = 0;
unsigned long GameTime::lastDelta = 0;
vector<pair<unsigned long, function<void()>>> GameTime::pendingEvents;
GameTime::timeprovider GameTime::_timeProvider = []() { return 0; };

std::map<GameTime::RepeatToken, unsigned long> GameTime::_repeatExecutionTimes{};
std::map<GameTime::RepeatToken, pair<unsigned long, function<void()>>> GameTime::_scheduledRepetitions{};