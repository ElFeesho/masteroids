#include "UFO.h"
#include "debris.h"
#include "engine.h"
#include <stdlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <ogc/lwp_watchdog.h>
#include "GRRLIB.h"

#include "ufobullet.h"

UFO::UFO() : next_think(ticks_to_millisecs(gettime())+1500), next_fire(ticks_to_millisecs(gettime())+450), alive(true), shipColour(RGB(1.0f, 0.0f, 1.0f))
{
	if(rand()%2)
	{
		X(-10);
		xspeed = 1.5;
	}
	else
	{
		X(650);
		xspeed = -1.5;
	}
	Y((rand()%400)+40);
	yspeed = 0;
	
	set_radius(10);
}

UFO::~UFO()
{
	
}

bool UFO::update(GfxWrapper *gfx)
{
	if(!alive)
		return false;

	unsigned long cticks = ticks_to_millisecs(gettime());
	if(cticks>next_think)
	{
		next_think+=1500;
		if(yspeed==0)
			yspeed = (((rand()%2)*-6)+3)/2.0;
		else
			yspeed = 0;
	}

	if(cticks>next_fire)
	{
		next_fire+=1000;
		get_engine()->add_entity(new UFOBullet(X(), Y(), ((rand()%5)*90)-45, this));
	}

	X(X()+xspeed);
	Y(Y()+yspeed);

	if(xspeed>0 && X()>650)
		return false;
	if(xspeed<0 && X()<-10)
		return false;

	if(Y()<-10)
		Y(490);

	if(Y()>490)
		Y(-10);

	/* COMPLEX DRAWING ROUTEIN!!! j/k */
	gfx->drawLine(X()-get_radius()/4,Y()-get_radius(), X()+get_radius()/4, Y()-get_radius(),shipColour);
	gfx->drawLine(X()-get_radius()/2,Y()+get_radius(), X()+get_radius()/2, Y()+get_radius(),shipColour);
	gfx->drawLine(X()-get_radius()/2,Y()+get_radius(), X()-get_radius(), Y()+get_radius()/2,shipColour);
	gfx->drawLine(X()+get_radius()/2,Y()+get_radius(), X()+get_radius(), Y()+get_radius()/2,shipColour);
	gfx->drawLine(X()-get_radius()/2,Y()-get_radius(), X()-get_radius(), Y()-get_radius()/2,shipColour);
	gfx->drawLine(X()+get_radius()/2,Y()-get_radius(), X()+get_radius(), Y()-get_radius()/2,shipColour);
	gfx->drawLine(X()+get_radius(),Y()-get_radius()/2, X()+get_radius(), Y()+get_radius()/2,shipColour);
	gfx->drawLine(X()-get_radius(),Y()-get_radius()/2, X()-get_radius(), Y()+get_radius()/2,shipColour);
	gfx->drawLine(X()-get_radius(),Y()+get_radius()/2, X()+get_radius(), Y()+get_radius()/2,shipColour);
	gfx->drawLine(X()-get_radius(),Y()-get_radius()/2, X()+get_radius(), Y()-get_radius()/2,shipColour);


	return true;
}

void UFO::on_hit()
{
	if(xspeed<0)
	{
		if(yspeed<0)
		{
			get_engine()->add_entity(new Debris(10, X(), Y(), -45, xspeed*2, yspeed*2, shipColour, 2500));
		}
		else
		{	
			get_engine()->add_entity(new Debris(10, X(), Y(), 225, xspeed*2, yspeed*2, shipColour, 2500));
		}
	}
	else
	{
		if(yspeed<0)
		{
			get_engine()->add_entity(new Debris(10, X(), Y(), 45, xspeed*2, yspeed*2, shipColour, 2500));
		}
		else
		{
			get_engine()->add_entity(new Debris(10, X(), Y(), 135, xspeed*2, yspeed*2, shipColour, 2500));
		}
	}

	alive = false;
}
