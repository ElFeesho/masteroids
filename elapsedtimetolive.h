#ifndef ELAPSEDTIMETOLIVE_H
#define ELAPSEDTIMETOLIVE_H

#include "alivemonitor.h"

class ElapsedTimeToLive : public AliveMonitor {
public:
    ElapsedTimeToLive(long ttl);

    ~ElapsedTimeToLive();

    bool alive();

private:
    long ttl;
};

#endif // ELAPSEDTIMETOLIVE_H
