#ifndef ELAPSEDTIMETOLIVE_H
#define ELAPSEDTIMETOLIVE_H

#include "alivemonitor.h"

class ElapsedTimeToLive : public AliveMonitor
{
public:
	ElapsedTimeToLive(unsigned long ttl);

	~ElapsedTimeToLive();

    bool alive() const;

private:
	unsigned long ttl;
};

#endif // ELAPSEDTIMETOLIVE_H
