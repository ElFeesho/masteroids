#include <gccore.h>
#include <ogc/lwp_watchdog.h>

#include <stdlib.h>

#include <math.h>

#include "debrisfragment.h"

DebrisFragment::DebrisFragment(Position position, double size, double rotationSpeed, double xspeed, double yspeed, const RGB &colour, long time_to_live) : pos(position), size(size), rotationSpeed(rotationSpeed), xspeed(xspeed), yspeed(yspeed), colour(colour), ttl(time_to_live)
{
	pos = position;
	ttl+=ticks_to_millisecs(gettime());
}

DebrisFragment::~DebrisFragment()
{

}

bool DebrisFragment::update()
{
	long ctime = ticks_to_millisecs(gettime());
	if(ctime>ttl)
	{
		return false;
	}
	
	position().translate(xspeed, yspeed);
	position().Rotation(rotationSpeed);
	
	return true;
}
void DebrisFragment::render(GfxWrapper* gfx)
{
	gfx->drawLine(position().X() + cos(position().Rotation()/180.0*M_PI)*size, 
					  position().Y() + sin(position().Rotation()/180.0*M_PI)*size, 
					  position().X() + (cos(position().Rotation()-180)/180.0*M_PI)*size,
					  position().Y() + (sin(position().Rotation()-180)/180.0*M_PI)*size,
					  colour);
}
