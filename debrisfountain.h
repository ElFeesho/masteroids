#ifndef DEBRISFOUNTAIN_H
#define DEBRISFOUNTAIN_H

#include "entitylist.h"
#include "direction.h"
#include "position.h"

#include "debris.h"

class DebrisFountain
{
public:
	DebrisFountain();
	~DebrisFountain();
	
	void projectDebris(Direction &direction, Position &from)
	{
	}
private:
};

#endif // DEBRISFOUNTAIN_H
