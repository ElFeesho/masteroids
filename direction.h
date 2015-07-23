#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <cmath>

class Direction
{
public:
    Direction(double speed, double angle, double spin = 0) : speed(speed), spin(spin), angle(angle)
	{
	}

	Direction(const Direction &copy) : speed(copy.speed), angle(copy.angle)
	{
	}

	~Direction()
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

	void rotate(double angle)
	{
		this->angle += angle;
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
