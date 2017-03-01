#pragma once

#include <movers/mover.h>

class FixedDirectionMover : public Mover
{
public:
	void move(Direction &direction, Position &position, Shape &shape) override;

	virtual void reset() override;
};