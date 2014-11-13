#ifndef DEBRIS_H
#define DEBRIS_H
#include "entity.h"
#include "gfx.h"
#include <cmath>
#import "time.h"

#include "fixeddirectionmover.h"

class ElapsedTimeToLive : public AliveMonitor
{
public:
	ElapsedTimeToLive(long ttl) : ttl(Time::getMillis()+ttl) {}
	~ElapsedTimeToLive() {}

	bool alive() {
		return Time::getMillis() < ttl;
	}
private:
	long ttl;
};

class Debris : public Entity
{
public:
	Debris(Direction travelDirection, Position pos, Shape shape);
	~Debris();

	Position& position();

	Shape& shape();

	Direction& direction();

	AliveMonitor &aliveMonitor() { return monitor; }

	void render(GfxWrapper* gfx);

	bool update();


private:
	Direction travelDirection;
	Position pos;
	Shape debrisShape;
	ElapsedTimeToLive monitor;
	double rotationSpeed;
	FixedDirectionMover mover;
};

#endif // DEBRIS_H
