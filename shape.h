#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:
	Shape();
	Shape(double radius);
	Shape(const Shape& other);
	~Shape();
	Shape& operator=(const Shape& other);
	bool operator==(const Shape& other) const;
	
	void Radius(double radius) { this->radius = radius; }
	double Radius() { return radius; }
	
	static Shape NONE;
private:
	double radius;
};

#endif // SHAPE_H
