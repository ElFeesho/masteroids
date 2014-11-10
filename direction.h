#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <cmath>

class Direction
{
public:
	Direction(double speed, double angle) : speed(speed), angle(angle) {}
	Direction(const Direction &copy) : speed(copy.speed), angle(copy.angle) {}
	~Direction() {}
	
	double Speed() { return speed; }
	double Angle() { return angle; }
	void Speed(double nSpeed) { speed = nSpeed; }
	void Angle(double nAngle) { angle = nAngle; }
	void rotate(double angle) { this->angle += angle; }
private:
	double speed, angle;
};

#endif
