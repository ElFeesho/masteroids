#pragma once

#include "mover.h"
#include "gametime.h"

class BulletMover : public Mover
{
public:
	BulletMover();

	~BulletMover();

	void move(Direction &direction, Position &position, Shape &shape = Shape::NONE);

	void reset();
};
