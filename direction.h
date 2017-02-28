#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <cmath>
#include <iostream>

class Direction
{
public:
    Direction(double initialSpeed, double initialAngle, double initialSpin = 0) : speed(initialSpeed), spin(initialSpin), angle(initialAngle)
	{
	}

	double Speed()
	{
		return speed;
	}

	double Angle()
	{
		return angle;
	}

	double Spin()
	{
		return spin;
	}

	void Spin(double nSpin)
	{
		spin = nSpin;
	}

	void Speed(double nSpeed)
	{
		speed = nSpeed;
	}

	void Angle(double nAngle)
	{
		angle = nAngle;
	}

	void rotate(double nAngle)
	{
		this->angle += nAngle;
	}


	bool operator==(const Direction &other) const
	{
		return (&other == &NONE) || ((other.speed == speed) && (other.angle == angle));
	}

	static Direction NONE;
private:
	double speed{0};
	double spin{0};
	double angle{0};
};

#endif
