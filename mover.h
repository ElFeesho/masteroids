#ifndef __MOVER_H__
#define __MOVER_H__

#include "position.h"
#include "direction.h"

class Mover
{
public:
	virtual ~Mover() {};
	virtual void move(Direction &direction, Position &position) = 0;
};

#endif
