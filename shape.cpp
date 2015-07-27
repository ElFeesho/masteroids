#include "shape.h"

Shape::Shape(double radius) : radius(radius) {}

void Shape::Radius(double radius) {
	this->radius = radius;
}

double Shape::Radius() {
	return radius;
}

bool Shape::operator==(Shape &rhs) {
	return radius == rhs.radius;
}

Shape Shape::NONE = Shape(0.0);