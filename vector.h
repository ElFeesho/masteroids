#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	Vector(double initialX, double initialY) : x(initialX), y(initialY)
	{
	}

	~Vector()
	{
	}

	double X()
	{
		return x;
	}

	double Y()
	{
		return y;
	}

	void X(double nx)
	{
		this->x = nx;
	}

	void Y(double ny)
	{
		this->y = ny;
	}

	void add(double nx, double ny)
	{
		this->x += nx;
		this->y += ny;
	}

private:
	double x{0};
	double y{0};
};

#endif // VECTOR_H
