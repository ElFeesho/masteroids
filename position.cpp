#include "position.h"

Position::Position(double initialX, double initialY, double angle) : x(initialX), y(initialY), rotation(angle)
{

}

Position::Position(const Position &other)
{
	x = other.x;
	y = other.y;
	rotation = other.rotation;
}

Position::~Position()
{

}

Position &Position::operator=(const Position &other)
{
	this->x = other.x;
	this->y = other.y;
	this->rotation = other.rotation;
	return *this;
}

bool Position::operator==(const Position &other) const
{
	return x == other.x && y == other.y && rotation == other.rotation;
}

bool Position::operator!=(const Position &other) const
{
	return x != other.x && y != other.y && rotation != other.rotation;
}

void Position::set(double nx, double ny, double angle)
{
	this->x = nx;
	this->y = ny;
	this->rotation = angle;
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
	this->y = ny;
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
	this->x += nx;
	this->y += ny;
}

Position Position::NONE = Position();

