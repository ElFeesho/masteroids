#include <vector>
#include "bullet.h"
#include "ship.h"
#include "options.h"
#include "collobj.h"
#include "engine.h"
#include <ogcsys.h>
#include <gccore.h>

#include <math.h>

#include <ogc/lwp_watchdog.h>

#include "GRRLIB.h"

using std::vector;

Bullet::Bullet()
{

}

Bullet::Bullet(double x, double y, double rot, unsigned short color, Entity *player) : angle(rot), col(color), owner(player), ttl(ticks_to_millisecs(gettime())+1500)
{
	X(x);
	Y(y);
}

Bullet::~Bullet()
{

}

bool Bullet::update()
{
	/* Collision Detection and barbaric treatment of CPU :( */
	for(vector<Collobj *>::iterator iter = get_engine()->get_collents()->begin(); iter!=get_engine()->get_collents()->end(); iter++)
	{
		if(!Options::team_kill) // Bumping into each other causes big BOOM :D
		{
			if((*iter) == Ship::players[0]||(*iter) == Ship::players[1]||(*iter) == Ship::players[2]||(*iter) == Ship::players[3])
				continue;
		}
		if((*iter)==owner)
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
				((Ship*)owner)->dec_bfired();
				((Ship*)owner)->add_score(30-(*iter)->get_radius());
				return false;
			}
	 	}
	}
	GRRLIB_DrawRectangle(X()-1,Y()-1,2,2,col,1);
	
	X(X()+cos(angle/180*M_PI)*3.5);
	Y(Y()+sin(angle/180*M_PI)*3.5);
	
	if(X()>640.0f)
		X(0.0f);
	if(X()<0.0f)
		X(640.0f);
	if(Y()>480.0f)
		Y(0.0f);
	if(Y()<0.0f)
		Y(480.0f);
	if(ticks_to_millisecs(gettime())>ttl)
	{
		((Ship*)owner)->dec_bfired();
		return false;
	}
	return true;
}
