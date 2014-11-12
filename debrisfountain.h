#ifndef DEBRISFOUNTAIN_H
#define DEBRISFOUNTAIN_H

#include "entitylist.h"
#include "direction.h"
#include "position.h"

#include "debris.h"

class DebrisFountain
{
public:
	DebrisFountain(const EntityList &entityList) : entList(entityList) {}
	~DebrisFountain() {}
	
	void projectDebris(Direction direction, Position from, double spread, int amount)
	{
		for(int i = 0; i < amount; i++)
		{
			entList.add(new Debris(direction, from, Shape(5.0f)));
		}
		printf("ENTLIST SIZE: %d\n", entList.size());
	}
private:
	EntityList entList;
};

#endif // DEBRISFOUNTAIN_H
