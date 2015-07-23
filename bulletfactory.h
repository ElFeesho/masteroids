#pragma once

#include <memory>

#include "movers/bulletmover.h"
#include "renderers/bulletrenderer.h"
#include "elapsedtimetolive.h"

#include "actor.h"

class BulletFactory
{
public:
	BulletFactory()
	{
	}

	~BulletFactory()
	{
	}

	Actor *createBullet(RGB &colour, Direction &direction, Position &position)
    {
        Actor *bullet = new Actor(colour, mover, renderer, std::unique_ptr<ElapsedTimeToLive>(new ElapsedTimeToLive(3000)));
		bullet->direction().Angle(direction.Angle());
		bullet->direction().Speed(direction.Speed());
		bullet->position().X(position.X());
		bullet->position().Y(position.Y());
		bullet->position().Rotation(position.Rotation());
		bullet->shape().Radius(1.0f);
		return bullet;
	}

private:
	BulletMover mover;
	BulletRenderer renderer;
};
