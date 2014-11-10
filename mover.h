#ifndef __MOVER_H__
#define __MOVER_H__

#include "position.h"
#include "direction.h"

class Mover
{
public:
	virtual ~Mover() {};
	virtual void move(Position &position) = 0;
	virtual void setDirection(Direction &direction) = 0;
};

#endif
