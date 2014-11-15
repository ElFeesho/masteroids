#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	Position();
	Position(double x, double y, double angle);
	Position(const Position& other);
	~Position();
	Position& operator=(const Position& other);
	bool operator==(const Position& other) const;
	
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
    double rotation;
    double y;
    double x;
};

#endif // POSITION_H
