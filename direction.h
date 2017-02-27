#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <cmath>
#include <iostream>

class Direction
{
public:
	Direction(double initialSpeed, double initialAngle, double initialSpin = 0);

	double Speed();

	double Angle();

	double Spin();

	void Spin(double nSpin);

	void Speed(double nSpeed);

	void Angle(double nAngle);

	void rotate(double nAngle);

	bool operator==(const Direction &other) const;

	static Direction NONE;
private:
	double speed{0};
	double spin{0};
	double angle{0};
};

#endif
