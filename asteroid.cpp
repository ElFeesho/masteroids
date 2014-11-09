#include "asteroid.h"
#include "options.h"
#include <cstdlib>
#include <cmath>

#include <ogcsys.h>
#include <gccore.h>
#include "engine.h"
#include "GRRLIB.h"

#include "debris.h"

Asteroid::Asteroid() : speed(0.0f), alive(true), rot((double)(rand()%360)), rot_speed(rand()%10-5), trav_ang(rand()%360), colour(RGB(1.0f, 1.0f, 1.0f))
{
	while(speed == 0)
	{
		speed = rand()%(Options::difficulty+2);
		if(rand()%2)
			speed*=-1;
	}
	set_radius(25.0f);
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

Asteroid::Asteroid(double scale) : speed(0), alive(true), rot((double)(rand()%360)), rot_speed(rand()%10-5), trav_ang(rand()%360), colour(RGB(1.0f, 1.0f, 1.0f))
{
	while(speed==0)
	{
		speed = rand()%(Options::difficulty+2);
		if(rand()%2)
			speed*=-1;
	}
	set_radius(scale);
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
}

bool Asteroid::update()
{
	rot+=rot_speed;
	position().translate(cos(trav_ang/180*M_PI)*speed, sin(trav_ang/180*M_PI)*speed);
	double radius = get_radius();
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
			double rot1 = (rot + i*72.0)/180.0*M_PI;
			double rot2 = (rot + (i+1) * 72.0)/180.0*M_PI;
			gfx->drawLine(position().X()+cos(rot1)*peaks[i], position().Y()+sin(rot1)*peaks[i], position().X()+cos(rot2)*peaks[i+1], position().Y()+sin(rot2)*peaks[i+1],colour);
		}
		else
		{
			double rot1 = (rot + i*72)/180.0*M_PI;
			double rot2 = rot/180.0*M_PI;
			gfx->drawLine(position().X()+cos(rot1)*peaks[i], position().Y()+sin(rot1)*peaks[i], position().X()+cos(rot2)*peaks[0], position().Y()+sin(rot2)*peaks[0],colour);
		}
	}
}


void Asteroid::on_hit()
{
	if(get_radius()>10.0f)
	{
		for(int i = 0; i<2; i++)
		{
			Asteroid *ast = new Asteroid(get_radius()/2.0f);
			ast->position().X(position().X()+rand()%((int)get_radius()*2)-get_radius());
			ast->position().Y(position().Y()+rand()%((int)get_radius()*2)-get_radius());
			//get_engine()->add_entity(ast);
			// TODO listener emit event
		}
	}
	//get_engine()->add_entity(new Debris(4,position().X(),position().Y(),rot,speed,speed,colour,1500));
	Asteroid::count--;
	alive = false;	
}

int Asteroid::count = 0;

