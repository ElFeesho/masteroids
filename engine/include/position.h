#pragma once

class Position
{
public:
	Position(double x, double y, double angle);

	bool operator==(const Position &other) const {
		return x == other.x && y == other.y && rotation == other.rotation;
	}

	void set(double x, double y, double rotation);

	double X();

	double Y();

	double Rotation();

	void X(double x);

	void Y(double y);

	void Rotation(double rotation);

	void rotate(double angle);

	void translate(double x, double y);

	static Position NONE;
private:
    double x{0};
    double y{0};
    double rotation{0};
};

