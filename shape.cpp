#include "shape.h"

Shape::Shape(double nradius) : radius(nradius) {}

void Shape::Radius(double nradius) {
	this->radius = nradius;
}

double Shape::Radius() {
	return radius;
}

bool Shape::operator==(Shape &rhs) {
	return radius == rhs.radius;
}
bool Shape::operator!=(Shape &rhs)
{
	return radius != rhs.radius;
}

Shape Shape::NONE = Shape(0.0);