#include "debrisfountain.h"
#include <actor.h>
#include <movers/fixeddirectionmover.h>
#include "renderers/debrisrenderer.h"
#include "elapsedtimetolive.h"

#include <cstdlib>
#include <cmath>

void DebrisFountain::projectDebris(EntityList &entityList, Direction direction, Position from, double spread, int amount, RGB &colour, float size)
{
	double startAngle = direction.Angle() - spread / 2.0;

	double angleStep = spread / (double) amount;
	for (int i = 0; i < amount; i++)
	{
		Direction debrisDirection{direction.Speed(), startAngle+angleStep*i, ((rand() % 10) / 10.f) - 0.5f};
		
		Actor *actor = new Actor(colour, mover, renderer, std::unique_ptr<ElapsedTimeToLive>(new ElapsedTimeToLive(1000)));
		actor->position().set(from.X(), from.Y(), from.Rotation());
		actor->direction().set(debrisDirection);
		actor->shape().Radius(size);

		entityList.add(actor);
	}
}
