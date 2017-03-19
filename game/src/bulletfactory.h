#pragma once

#include <memory>

#include <movers/fixeddirectionmover.h>
#include "renderers/bulletrenderer.h"
#include "elapsedtimetolive.h"

#include <actor.h>

class BulletFactory
{
public:
    Actor *createBullet(RGB &colour, Direction direction, Position position);

private:
	FixedDirectionMover mover;
	BulletRenderer renderer;
};
