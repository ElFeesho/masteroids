#include "shape.h"

Shape::Shape()
{

}

Shape::Shape(const Shape& other)
{
	radius = other.radius;
}

Shape::~Shape()
{

}

Shape& Shape::operator=(const Shape& other)
{
	radius = other.radius;
}

bool Shape::operator==(const Shape& other) const
{
	return other.radius == radius || this == &other;
}

Shape Shape::NONE = Shape();