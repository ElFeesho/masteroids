#include "position.h"

Position::Position()
{

}

Position::Position(const Position& other)
{

}

Position::~Position()
{

}

Position& Position::operator=(const Position& other)
{

}

bool Position::operator==(const Position& other) const
{
	return x == other.x && y == other.y && rotation == other.rotation;
}

double Position::X()
{
	return x;
}

void Position::X(double x)
{
	this->x = x;
}


double Position::Y()
{
	return y;
}

void Position::Y(double y)
{
	this->y = y;
}


double Position::Rotation()
{
	return rotation;
}

void Position::Rotation(double rotation)
{
	this->rotation = rotation;
}

void Position::rotate(double angle)
{
	rotation += angle;
}

void Position::translate(double x, double y)
{
	this->x += x;
	this->y += y;
}

