#include <gccore.h>
#include <ogc/lwp_watchdog.h>

#include <stdlib.h>

#include <math.h>

#include "debris.h"

Debris::Debris(int amount, double xpos, double ypos, double angle, double xspeed, double yspeed, const RGB &colour, long time_to_live) : count(amount), colour(colour), ttl(time_to_live)
{
	if(count > 16) // If there are more than 16 pieces of shrapnel, bail
	{
		count = 0;
		ttl = 0;
		return;
	}
	ttl+=ticks_to_millisecs(gettime());
	for(int i = 0;i<count;i++)
	{
		x[i] = xpos;//+((rand()%16)-8);
		y[i] = ypos;//+((rand()%16)-8);
		angles[i] = (angle+((rand()%60)-30))/180.0*M_PI; // 30 degree spread
		rot_speed[i] = rand()%20-10;
		xsp[i] = cos(angles[i])*xspeed;
		//+((rand()%(int)(xspeed/4.0))-(xspeed/8.0)));
		ysp[i] = sin(angles[i])*yspeed;
		sizes[i] = (rand()%5)+5;
	}
}

Debris::~Debris()
{

}

bool Debris::update()
{
	long ctime = ticks_to_millisecs(gettime());
	if(ctime>ttl)
	{
		return false;
	}

	/* double diff = 1.0-(double)(ctime)/(double)(ttl); For later */

	for(int i = 0; i<count; i++)
	{
		x[i]+=xsp[i];
		y[i]+=ysp[i];
		if(x[i]>640+sizes[i])
		{
			x[i] = -sizes[i];
		}
		
		if(x[i]<0-sizes[i])
		{
			x[i] = 640+sizes[i];
		}
		
		if(y[i]>480+sizes[i])
		{
			y[i] = -sizes[i];
		}
		
		if(y[i]<0-sizes[i])
		{
			y[i] = 480+sizes[i];
		}
		
		// Cheeky chappy: gonna use angles[] again but for the rotation of the 
		// debris, since xsp and ysp is constant now, they don't depend on it
		if(i & 1)
		{
			angles[i]+=rot_speed[i];
		}
		else
		{
			angles[i]-=rot_speed[i];
		}
	}
	
	return true;
}
void Debris::render(GfxWrapper* gfx)
{
	for(int i = 0; i<count; i++)
	{
		gfx->drawLine(x[i]+cos(angles[i]/180.0*M_PI)*sizes[i],y[i]+sin(angles[i]/180.0*M_PI)*sizes[i],x[i]+cos((angles[i]-180)/180.0*M_PI)*sizes[i],y[i]+sin((angles[i]-180)/180.0*M_PI)*sizes[i],colour);
	}
}
