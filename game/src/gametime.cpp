#include "gametime.h"

long GameTime::lastTick = 0;
long GameTime::lastDelta = 0;
vector<pair<long, function<void()>>> GameTime::pendingEvents;
sf::Clock GameTime::clockTime;