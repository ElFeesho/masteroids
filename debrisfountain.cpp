#include "debrisfountain.h"

void DebrisFountain::projectDebris(EntityList &entityList, Direction direction, Position from, double spread, int amount, RGB &colour)
{
	double startAngle = direction.Angle() - spread / 2.0;
	direction.Angle(startAngle);
	double angleStep = spread / (double) amount;
	for (int i = 0; i < amount; i++)
	{
		entityList.add(std::make_shared<Debris>(direction, from, Shape(5.0f), colour));
		direction.rotate(angleStep);
	}
}
