#include "asteroid.h"
#include "options.h"
#include <cstdlib>
#include <cmath>

#include <ogcsys.h>
#include <gccore.h>
#include "engine.h"
#include "GRRLIB.h"

#include "debrisfragment.h"

static inline double createSpeed()
{
	double speed = 1+(rand() % (Options::difficulty+2));
	if(rand()%2 == 1)
	{
		speed *= -1;
	}
	return speed;
}

Asteroid::Asteroid() : mover(NULL), alive(true), rot_speed(rand()%10-5)
{
	mover = new AsteroidMover(Direction(createSpeed(), rand() % 360));
	position().Rotation(rand()%360);
	shape().Radius(25.0f);

	int pos = rand()%4;
	switch(pos)
	{
		case 0: // Top row
			position().X(rand()%160*4);
			position().Y(-25.0f);
			break;
		case 1: // Bottom row
			position().X(rand()%160*4);
			position().Y(480+25.0f);
			break;
		case 2: // Left column
			position().Y(rand()%120*4);
			position().X(-25.0f);
			break;
		case 3: // Right column
			position().Y(rand()%120*4);
			position().X(640+25.0f);
			break;
	}

	for(int i = 0;i<6;i++)
	{
		peaks[i] = 25.0f+(rand()%20-10);
	}
	Asteroid::count++;
}

Asteroid::Asteroid(double scale) : mover(NULL), alive(true), rot_speed(rand()%10-5)
{
	mover = new AsteroidMover(Direction(createSpeed(), rand() % 360));
	position().Rotation(rand()%360);
	shape().Radius(scale);

	int pos = rand()%4;
	switch(pos)
	{
		case 0: // Top row
			position().X(rand()%160*4);
			position().Y(-scale);
			break;
		case 1: // Bottom row
			position().X(rand()%160*4);
			position().Y(480+scale);
			break;
		case 2: // Left column
			position().Y(rand()%120*4);
			position().X(-scale);
			break;
		case 3: // Right column
			position().Y(rand()%120*4);
			position().X(640+scale);
			break;
	}

	for(int i = 0;i<6;i++)
	{
		peaks[i] = scale+(rand()%(int)(scale/2)-(scale/4));
	}
	Asteroid::count++;
}

Asteroid::~Asteroid()
{
	delete mover;
}

bool Asteroid::update()
{
	position().rotate(rot_speed);
	mover->move(position());

	double radius = shape().Radius();
	if(position().X()>640.0f+radius)
		position().X(0.0f-radius);

	if(position().X()<0.0f-radius)
		position().X(640.0f+radius);

	if(position().Y()>480.0f+radius)
		position().Y(0.0f-radius);

	if(position().Y()<0.0f-radius)
		position().Y(480.0f+radius);

	return alive;
}

void Asteroid::render(GfxWrapper* gfx)
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


void Asteroid::on_hit()
{
	int radius = shape().Radius();
	int diameter = radius*2;

	if(radius > 10.0f)
	{
		for(int i = 0; i<2; i++)
		{
			Asteroid *ast = new Asteroid(radius / 2.0f);
			ast->position().X(position().X()+rand()%(diameter)-radius);
			ast->position().Y(position().Y()+rand()%(diameter)-radius);
			//get_engine()->add_entity(ast);
			// TODO listener emit event
		}
	}
	//get_engine()->add_entity(new Debris(4,position().X(),position().Y(),rot,speed,speed,colour,1500));
	Asteroid::count--;
	alive = false;
}

int Asteroid::count = 0;

