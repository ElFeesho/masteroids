#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <cmath>

class Direction
{
public:
	Direction(double speed, double angle) : speed(speed), angle(angle) {}
	~Direction() {}
	double Speed() { return speed; }
	double Angle() { return angle/(180*M_PI); }

private:
	double speed, angle;
};

#endif
