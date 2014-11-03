#include "asteroid.h"
#include "options.h"
#include <cstdlib>
#include <cmath>

#include <ogcsys.h>
#include <gccore.h>
#include "engine.h"
#include "GRRLIB.h"

#include "debris.h"

Asteroid::Asteroid() : speed(0.0f), alive(true), rot((double)(rand()%360)), rot_speed(rand()%10-5), trav_ang(rand()%360)
{
	while(speed==0)
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
			this->X(rand()%160*4);
			this->Y(-25.0f);
			break;
		case 1: // Bottom row
			this->X(rand()%160*4);
			this->Y(480+25.0f);
			break;
		case 2: // Left column
			this->Y(rand()%120*4);
			this->X(-25.0f);
			break;
		case 3: // Right column
			this->Y(rand()%120*4);
			this->X(640+25.0f);
			break;
	}

	for(int i = 0;i<6;i++)
	{
		peaks[i] = 25.0f+(rand()%20-10);
	}
	Asteroid::count++;
}

Asteroid::Asteroid(double scale) : speed(0), alive(true), rot((double)(rand()%360)), rot_speed(rand()%10-5), trav_ang(rand()%360)
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
			this->X(rand()%160*4);
			this->Y(-scale);
			break;
		case 1: // Bottom row
			this->X(rand()%160*4);
			this->Y(480+scale);
			break;
		case 2: // Left column
			this->Y(rand()%120*4);
			this->X(-scale);
			break;
		case 3: // Right column
			this->Y(rand()%120*4);
			this->X(640+scale);
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
	X(X()+cos(trav_ang/180*M_PI)*speed);
	Y(Y()+sin(trav_ang/180*M_PI)*speed);
	double radius = get_radius();
	if(X()>640.0f+radius)
		X(0.0f-radius);

	if(X()<0.0f-radius)
		X(640.0f+radius);

	if(Y()>480.0f+radius)
		Y(0.0f-radius);

	if(Y()<0.0f-radius)
		Y(480.0f+radius);


	for(int i = 0;i<6;i++)
	{
		if(i!=5)
		{	
			double rot1 = (rot + i*72.0)/180.0*M_PI;
			double rot2 = (rot + (i+1) * 72.0)/180.0*M_PI;
			GRRLIB_Line(X()+cos(rot1)*peaks[i],Y()+sin(rot1)*peaks[i],X()+cos(rot2)*peaks[i+1],Y()+sin(rot2)*peaks[i+1],0xffff);
		}
		else
		{
			double rot1 = (rot + i*72)/180.0*M_PI;
			double rot2 = rot/180.0*M_PI;
			GRRLIB_Line(X()+cos(rot1)*peaks[i],Y()+sin(rot1)*peaks[i],X()+cos(rot2)*peaks[0],Y()+sin(rot2)*peaks[0],0xffff);
		}
	}
	return alive;
}

void Asteroid::on_hit()
{
	if(get_radius()>10.0f)
	{
		for(int i = 0; i<2; i++)
		{
			Asteroid *ast = new Asteroid(get_radius()/2.0f);
			ast->X(X()+rand()%((int)get_radius()*2)-get_radius());
			ast->Y(Y()+rand()%((int)get_radius()*2)-get_radius());
			get_engine()->add_entity(ast);
		}
	}
	get_engine()->add_entity(new Debris(4,X(),Y(),rot,speed,speed,0xffff,1500));
	Asteroid::count--;
	alive = false;	
}

int Asteroid::count = 0;

