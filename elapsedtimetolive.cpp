#include "elapsedtimetolive.h"
#include "gametime.h"

ElapsedTimeToLive::ElapsedTimeToLive(unsigned long nttl) : ttl(GameTime::getMillis() + nttl)
{

}

bool ElapsedTimeToLive::alive() const
{
	return GameTime::getMillis() < ttl;
}
