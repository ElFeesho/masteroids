#include "direction.h"

Direction Direction::NONE = Direction(0, 0);

Direction::Direction(double initialSpeed, double initialAngle, double initialSpin)
        : speed(initialSpeed), spin(initialSpin), angle(initialAngle) {
    std::cout << "Direction" << std::endl;
}

double Direction::Speed() {
    return speed;
}

double Direction::Angle() {
    return angle;
}

double Direction::Spin() {
    return spin;
}

void Direction::Spin(double nSpin) {
    spin = nSpin;
}

void Direction::Speed(double nSpeed) {
    speed = nSpeed;
}

void Direction::Angle(double nAngle) {
    angle = nAngle;
}

void Direction::rotate(double nAngle) {
    this->angle += nAngle;
}

bool Direction::operator==(const Direction &other) const {
    return (&other == &NONE) || ((other.speed == speed) && (other.angle == angle));
}