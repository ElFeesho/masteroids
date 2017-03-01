#ifndef FIXEDDIRECTIONMOVER_H
#define FIXEDDIRECTIONMOVER_H

#include "mover.h"
#include <cmath>

class FixedDirectionMover : public Mover
{
public:
	void move(Direction &direction, Position &position, Shape &shape) override;

	virtual void reset() override;
};

#endif // FIXEDDIRECTIONMOVER_H
