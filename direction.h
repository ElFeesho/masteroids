#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <cmath>

class Direction {
public:
    Direction() : speed(0), spin(0), angle(0) {}

    Direction(double speed, double angle, double spin = 0) : speed(speed), angle(angle), spin(spin) {
    }

    Direction(const Direction &copy) : speed(copy.speed), angle(copy.angle) {
    }

    ~Direction() {
    }

    double Speed() {
        return speed;
    }

    double Spin()
    {
        return spin;
    }

    void Spin(double spin)
    {
        this->spin = spin;
    }

    double Angle() {
        return angle;
    }

    void Speed(double nSpeed) {
        speed = nSpeed;
    }

    void Angle(double nAngle) {
        angle = nAngle;
    }

    void rotate(double angle) {
        this->angle += angle;
    }

    bool operator==(const Direction &other) const {
        return (&other == &NONE) || ((other.speed == speed) && (other.angle == angle));
    }

    static Direction NONE;
private:
    double speed, spin, angle;
};

#endif
