#pragma once

#include <vector>
#include <utility>
#include <functional>

using std::vector;
using std::pair;
using std::function;

class GameTime
{
public:
	using timeprovider = std::function<long()>;
	static void setTimeProvider(timeprovider timeProvider);
	static unsigned long getMillis();
	static void tick();
	static double factorTime(double input);
	static void schedule(long delay, function<void()> event);

private:

	static double timeMultiplier();

	static vector<pair<long, function<void()>>> pendingEvents;

	static long lastTick;
	static long lastDelta;

	static timeprovider _timeProvider;
};
