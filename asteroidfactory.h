#include <movers/fixeddirectionmover.h>
#include "actor.h"

#ifndef __ASTEROID_FACTORY_H__
#define __ASTEROID_FACTORY_H__

#include "renderers/asteroidrenderer.h"

static inline double randomAngle()
{
	double factor = rand() / (double) RAND_MAX;
	return (M_PI * 2.0f) * factor;
}

static inline double randomSpeed()
{
	double factor = rand() / (double) RAND_MAX;
	double speed = 3.0f * factor;
	return speed + 0.5f;
}

static inline double randomSpin()
{
	double factor = rand() / (double) RAND_MAX;
	double speed = 0.05f + (0.1f * factor);

	speed *= (rand() % 1000 > 500) ? -1 : 1;
	return speed;
}


class AsteroidFactory
{
public:
	AsteroidFactory()
			: renderers{AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer()},
			  mover(FixedDirectionMover())
	{

	}

	~AsteroidFactory()
	{

	}

	Actor *createAsteroid(double radius, Position &pos = Position::NONE)
	{
		Actor *asteroid = new Actor(RGB::white, &mover, &renderers[rand() % 5], &AlwaysAlive::alivemonitor);
		asteroid->shape().Radius(radius);
		asteroid->direction().Angle(randomAngle());
		asteroid->direction().Speed(randomSpeed());
		asteroid->direction().Spin(randomSpin());
		asteroid->position().X(pos.X());
		asteroid->position().Y(pos.Y());
		asteroid->position().Rotation(pos.Rotation());
		return asteroid;
	}

private:
	AsteroidRenderer renderers[5];
	FixedDirectionMover mover;
};

#endif