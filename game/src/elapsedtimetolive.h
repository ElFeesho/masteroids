#pragma once
#include "alivemonitor.h"

class ElapsedTimeToLive : public AliveMonitor
{
public:
	ElapsedTimeToLive(unsigned long ttl);

    bool alive() const;

private:
	unsigned long ttl;
};
