#include "UFO.h"
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
		position().X(-10);
		xspeed = 1.5;
	}
	else
	{
		position().X(650);
		xspeed = -1.5;
	}
	position().Y((rand()%400)+40);
	yspeed = 0;
	
	shape().Radius(10);
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
		//get_engine()->add_entity(new UFOBullet(X(), Y(), ((rand()%5)*90)-45, this));
	}

	position().translate(xspeed, yspeed);

	if(xspeed>0 && position().X()>650)
		return false;
	if(xspeed<0 && position().X()<-10)
		return false;

	if(position().Y()<-10)
		position().Y(490);

	if(position().Y()>490)
		position().Y(-10);

	/* COMPLEX DRAWING ROUTEIN!!! j/k */
	gfx->drawLine(position().X()-shape().Radius()/4,position().Y()-shape().Radius(), position().X()+shape().Radius()/4, position().Y()-shape().Radius(),shipColour);
	gfx->drawLine(position().X()-shape().Radius()/2,position().Y()+shape().Radius(), position().X()+shape().Radius()/2, position().Y()+shape().Radius(),shipColour);
	gfx->drawLine(position().X()-shape().Radius()/2,position().Y()+shape().Radius(), position().X()-shape().Radius(), position().Y()+shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()+shape().Radius()/2,position().Y()+shape().Radius(), position().X()+shape().Radius(), position().Y()+shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()-shape().Radius()/2,position().Y()-shape().Radius(), position().X()-shape().Radius(), position().Y()-shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()+shape().Radius()/2,position().Y()-shape().Radius(), position().X()+shape().Radius(), position().Y()-shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()+shape().Radius(),position().Y()-shape().Radius()/2, position().X()+shape().Radius(), position().Y()+shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()-shape().Radius(),position().Y()-shape().Radius()/2, position().X()-shape().Radius(), position().Y()+shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()-shape().Radius(),position().Y()+shape().Radius()/2, position().X()+shape().Radius(), position().Y()+shape().Radius()/2,shipColour);
	gfx->drawLine(position().X()-shape().Radius(),position().Y()-shape().Radius()/2, position().X()+shape().Radius(), position().Y()-shape().Radius()/2,shipColour);


	return true;
}

void UFO::on_hit()
{
	if(xspeed<0)
	{
		if(yspeed<0)
		{
			//get_engine()->add_entity(new Debris(10, X(), Y(), -45, xspeed*2, yspeed*2, shipColour, 2500));
		}
		else
		{	
			//get_engine()->add_entity(new Debris(10, X(), Y(), 225, xspeed*2, yspeed*2, shipColour, 2500));
		}
	}
	else
	{
		if(yspeed<0)
		{
			//get_engine()->add_entity(new Debris(10, X(), Y(), 45, xspeed*2, yspeed*2, shipColour, 2500));
		}
		else
		{
			//get_engine()->add_entity(new Debris(10, X(), Y(), 135, xspeed*2, yspeed*2, shipColour, 2500));
		}
	}

	alive = false;
}
