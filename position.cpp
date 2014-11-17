#include "position.h"

Position::Position() : x(0), y(0), rotation(0) {

}

Position::Position(double x, double y, double angle) : x(x), y(y), rotation(angle) {

}

Position::Position(const Position &other) {
    x = other.x;
    y = other.y;
    rotation = other.rotation;
}

Position::~Position() {

}

Position &Position::operator=(const Position &other) {
    this->x = other.x;
    this->y = other.y;
    this->rotation = other.rotation;
    return *this;
}

bool Position::operator==(const Position &other) const {
    return x == other.x && y == other.y && rotation == other.rotation;
}

double Position::X() {
    return x;
}

void Position::X(double x) {
    this->x = x;
}


double Position::Y() {
    return y;
}

void Position::Y(double y) {
    this->y = y;
}


double Position::Rotation() {
    return rotation;
}

void Position::Rotation(double rotation) {
    this->rotation = rotation;
}

void Position::rotate(double angle) {
    rotation += angle;
}

void Position::translate(double x, double y) {
    this->x += x;
    this->y += y;
}

Position Position::NONE = Position();

