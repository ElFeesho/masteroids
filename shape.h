#pragma once

class Shape
{
public:
	explicit Shape(double radius);

	void Radius(double radius);

	double Radius();

	static Shape NONE;

	bool operator==(Shape &rhs);
	bool operator!=(Shape &rhs);
private:
	double radius { 0 };
};
