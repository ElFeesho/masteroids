#pragma once

#include <memory>

#include <movers/fixeddirectionmover.h>
#include <actor.h>
#include "renderers/asteroidrenderer.h"

class AsteroidFactory
{
public:
	Actor *createAsteroid(double radius, Position pos = Position::NONE);
private:
	AsteroidRenderer renderers[5] {AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer(), AsteroidRenderer()};
	FixedDirectionMover mover;
};
