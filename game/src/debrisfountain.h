#pragma once

#include "entitylist.h"
#include <movers/fixeddirectionmover.h>
#include "renderers/debrisrenderer.h"
#include <direction.h>
#include <position.h>

class DebrisFountain
{
public:
	void projectDebris(EntityList &entityList, Direction direction, Position from, double spread, int amount, RGB &colour, float size);
private:
	FixedDirectionMover mover;
	DebrisRenderer renderer;
};

