#include "shape.h"

Shape::Shape() {

}

Shape::Shape(const Shape &other) {
    radius = other.radius;
}

Shape::~Shape() {

}

Shape &Shape::operator=(const Shape &other) {
    radius = other.radius;
    return *this;
}

bool Shape::operator==(const Shape &other) const {
    return other.radius == radius || this == &other;
}

Shape::Shape(double radius) : radius(radius) {
}

Shape Shape::NONE = Shape();
