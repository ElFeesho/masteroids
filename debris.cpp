#include "debris.h"
#include <cstdlib>

Debris::Debris(Direction ntravelDirection, Position npos, Shape shape, RGB &debrisColour) :
		travelDirection(ntravelDirection),
		pos(npos),
        debrisShape(shape),
        colour(debrisColour),
        rotationSpeed(((rand() % 10) / 10.f) - 0.5f),
        monitor(1500)
{
	std::cout << "Debris" << std::endl;
}

Debris::~Debris()
{
	std::cout << "~Debris" << std::endl;
}

Position &Debris::position()
{
	return pos;
}

Shape &Debris::shape()
{
	return debrisShape;
}

Direction &Debris::direction()
{
	return travelDirection;
}

void Debris::render(Gfx &gfx)
{
	renderer().render(gfx, position(), shape(), direction(), colour);
}

bool Debris::update()
{
	mover.move(direction(), position(), shape());
	position().rotate(rotationSpeed);
	return aliveMonitor().alive();
}

const AliveMonitor &Debris::aliveMonitor() {
	return monitor;
}

const Renderer &Debris::renderer() {
	return debrisRenderer;
}