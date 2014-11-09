#include <vector>
#include "ufobullet.h"
#include "UFO.h"
#include "options.h"
#include "collobj.h"
#include "engine.h"
#include <ogcsys.h>
#include <gccore.h>

#include <math.h>

#include <ogc/lwp_watchdog.h>

#include "GRRLIB.h"

using std::vector;

UFOBullet::UFOBullet()
{

}

UFOBullet::UFOBullet(double x, double y, double rot, Entity *ufo) : angle(rot), owner(ufo), ttl(ticks_to_millisecs(gettime())+1500)
{
	position().X(x);
	position().Y(y);
}

UFOBullet::~UFOBullet()
{

}

bool UFOBullet::update()
{
	/* Collision Detection and barbaric treatment of CPU :( 
	for(vector<Collobj *>::iterator iter = get_engine()->get_collents()->begin(); iter!=get_engine()->get_collents()->end(); iter++)
	{
		if((*iter) == owner)
			continue;
		double ax, ay, ar;
		ax = (*iter)->X();
		ay = (*iter)->Y();
		ar = (*iter)->get_radius();

		if(X()>ax-ar && X()<ax+ar && Y()>ay-ar && Y()<ay+ar)
		{
			// High res collision detection now peeps! Circular collision detection
			if(((ax-X())*(ax-X()))+((ay-Y())*(ay-Y()))<(ar*ar))
			{
	 			// By jove we've got a hit!
				(*iter)->on_hit();
				ttl = 0;
			}
	 	}
	}
	*/

	position().translate(cos(angle/180*M_PI)*3.5, sin(angle/180*M_PI)*3.5);

	if(position().X()>640.0f)
	{
		position().X(0.0f);
	}

	if(position().X()<0.0f)
	{
		position().X(640.0f);
	}
	if(position().Y()>480.0f)
	{
		position().Y(0.0f);
	}
	if(position().Y()<0.0f)
	{
		position().Y(480.0f);
	}

	return ticks_to_millisecs(gettime()) < ttl;
}

void UFOBullet::render(GfxWrapper* gfx)
{
	gfx->drawRect(position().X()-1, position().Y()-1, 2, 2, RGB::purple);
}
