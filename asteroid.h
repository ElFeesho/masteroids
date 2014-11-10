#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "entity.h"
#include "gfx.h"

#include "mover.h"

#include <cmath>

class AsteroidMover : public Mover
{
public:
	AsteroidMover(const Direction &direction) : direction(direction) {}
	~AsteroidMover() {};

	void move(Position &position) {
		position.translate(cos(direction.Angle())*direction.Speed(), sin(direction.Angle())*direction.Speed());
	};

	void setDirection(Direction &direction)
	{
		this->direction = direction;
	}
private:
	Direction direction;
};

class Asteroid : public Entity
{
public:
	Asteroid();
	Asteroid(double scale);
	~Asteroid();

	bool update();
	void render(GfxWrapper *gfx);
	void on_hit();
	static int count;
	Position &position() { return pos; }
	Shape &shape() { return asteroidShape; }
private:
	Mover *mover;
	Position pos;
	Shape asteroidShape;
	double peaks[6];
	bool alive;
	double rot_speed;
};

#endif
