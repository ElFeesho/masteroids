#pragma once

#include <memory>

#include <movers/fixeddirectionmover.h>
#include "renderers/bulletrenderer.h"
#include "elapsedtimetolive.h"

#include <actor.h>

class BulletFactory
{
public:
    Actor *createBullet(RGB &colour, Direction direction, Position position)
    {
        Actor *bullet = new Actor(colour, mover, renderer, std::unique_ptr<ElapsedTimeToLive>(new ElapsedTimeToLive(3000)));
		bullet->direction().set(direction);
		bullet->position().set(position.X(), position.Y(), position.Rotation());
		bullet->shape().Radius(1.0f);
		return bullet;
	}

private:
	FixedDirectionMover mover;
	BulletRenderer renderer;
};
