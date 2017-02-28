#include <position.h>

Position::Position(double initialX, double initialY, double angle) : x(initialX), y(initialY), rotation(angle)
{
}

void Position::set(double nx, double ny, double angle)
{
	x = nx;
	y = ny;
	rotation = angle;
}

double Position::X()
{
	return x;
}

void Position::X(double nx)
{
	this->x = nx;
}


double Position::Y()
{
	return y;
}

void Position::Y(double ny)
{
	y = ny;
}

double Position::Rotation()
{
	return rotation;
}

void Position::Rotation(double nrotation)
{
	this->rotation = nrotation;
}

void Position::rotate(double nangle)
{
	rotation += nangle;
}

void Position::translate(double nx, double ny)
{
	x += nx;
	y += ny;
}

Position Position::NONE = Position(0, 0, 0);

