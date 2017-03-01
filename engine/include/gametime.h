#pragma once

#include <vector>
#include <utility>
#include <functional>
#include <map>

using std::vector;
using std::pair;
using std::function;

class GameTime
{
public:
	using RepeatToken = int;

	using timeprovider = std::function<long()>;
	static void setTimeProvider(timeprovider timeProvider);
	static unsigned long getMillis();
	static void tick();
	static double factorTime(double input);
	static void schedule(unsigned long delay, function<void()> event);
	static RepeatToken scheduleRepeating(unsigned long interval, function<void()> event);
	static void removeRepeating(RepeatToken eventToken);
private:

	static double timeMultiplier();

	static vector<pair<unsigned long, function<void()>>> pendingEvents;

	static unsigned long lastTick;
	static unsigned long lastDelta;

	static timeprovider _timeProvider;

	static std::map<RepeatToken, unsigned long> _repeatExecutionTimes;
	static std::map<RepeatToken, pair<unsigned long, function<void()>>> _scheduledRepetitions;
};
