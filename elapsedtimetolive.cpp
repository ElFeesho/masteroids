#include "elapsedtimetolive.h"
#include "gametime.h"

ElapsedTimeToLive::ElapsedTimeToLive(long int ttl) : ttl(GameTime::getMillis() + ttl) {

}

ElapsedTimeToLive::~ElapsedTimeToLive() {

}

bool ElapsedTimeToLive::alive() {
    return GameTime::getMillis() < ttl;
}
