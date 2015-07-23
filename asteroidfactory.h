#pragma once

#include <memory>

#include "movers/fixeddirectionmover.h"
#include "actor.h"

#ifdef __WII__
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#endif

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
            Actor *asteroid = new Actor(RGB::white, mover, renderers[rand() % 5], std::unique_ptr<AlwaysAlive>(new AlwaysAlive()));
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
