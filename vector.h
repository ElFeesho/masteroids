#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	Vector(double x, double y) : x(x), y(y) {}
	~Vector() {}
	
	double X() { return x; }
	double Y() { return y; }
	
	void X(double x) { this->x = x; }
	void Y(double y) { this->y = y; }
	
	void add(double x, double y) { this->x += x; this->y += y; }
	
private:
    double x;
    double y;
};

#endif // VECTOR_H
