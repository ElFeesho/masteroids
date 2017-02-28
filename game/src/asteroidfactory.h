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

class AsteroidFactory
{
public:
	AsteroidFactory();

	Actor * createAsteroid(double radius, Position pos = Position::NONE);

private:
	AsteroidRenderer renderers[5];
	FixedDirectionMover mover;
};
