#pragma once

class Position
{
public:
    Position() = default;

	Position(double x, double y, double angle);

	Position(const Position &other);

	~Position();

	Position &operator=(const Position &other);

	bool operator==(const Position &other) const;

	bool operator!=(const Position &other) const;

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

