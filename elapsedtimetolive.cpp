#include "elapsedtimetolive.h"
#include "time.h"

ElapsedTimeToLive::ElapsedTimeToLive(long int ttl): ttl(Time::getMillis()+ttl) 
{
	
}

ElapsedTimeToLive::~ElapsedTimeToLive() 
{
	
}

bool ElapsedTimeToLive::alive()
{
	return Time::getMillis() < ttl;
}
