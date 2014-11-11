#ifndef FIXEDDIRECTIONMOVER_H
#define FIXEDDIRECTIONMOVER_H

#include "mover.h"
#include <cmath>


class FixedDirectionMover : public Mover
{
public:
	FixedDirectionMover(Direction direction);
	~FixedDirectionMover();
	
	void move(Position &position);;
	void setDirection(Direction &direction);
private:
	Direction direction;
};

#endif // FIXEDDIRECTIONMOVER_H
