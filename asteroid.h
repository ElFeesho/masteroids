#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <cmath>

#include "entity.h"
#include "gfx.h"

#include "fixeddirectionmover.h"

class AsteroidRenderer : public Renderer
{
public:
	AsteroidRenderer() 
	{
		for(int i = 0;i<6;i++)
		{
			peaks[i] = 25.0f+(rand()%20-10);
		}
	}
	
	void render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
	{
		for(int i = 0;i<6;i++)
	{
		if(i!=5)
		{
			double rot1 = (position().Rotation() + i*72.0)/180.0*M_PI;
			double rot2 = (position().Rotation() + (i+1) * 72.0)/180.0*M_PI;

			gfx->drawLine(position().X()+cos(rot1)*peaks[i], position().Y()+sin(rot1)*peaks[i], position().X()+cos(rot2)*peaks[i+1], position().Y()+sin(rot2)*peaks[i+1], RGB::white);
		}
		else
		{
			double rot1 = (position().Rotation() + i*72)/180.0*M_PI;
			double rot2 = position().Rotation()/180.0*M_PI;
			gfx->drawLine(position().X()+cos(rot1)*peaks[i], position().Y()+sin(rot1)*peaks[i], position().X()+cos(rot2)*peaks[0], position().Y()+sin(rot2)*peaks[0], RGB::white);
		}
	}
	}
	
private:
	double peaks[6];
};

class Asteroid : public Entity
{
public:
	Asteroid();
	Asteroid(double scale, const Position& nposition);
	~Asteroid();

	bool update();
	void render(GfxWrapper *gfx);
	Position &position() { return pos; }
	Shape &shape() { return asteroidShape; }
	Direction& direction() { return travelDirection; }
	AliveMonitor &aliveMonitor() { return AlwaysAlive::alivemonitor; }
private:
	Mover *mover;
	Position pos;
	Shape asteroidShape;
	Direction travelDirection;
	double peaks[6];
	bool alive;
	double rot_speed;
};

#endif
