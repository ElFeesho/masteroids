#include <vector>
#include "bullet.h"
#include "ship.h"
#include "options.h"
#include "engine.h"
#include <ogcsys.h>
#include <gccore.h>

#include <math.h>

#include <ogc/lwp_watchdog.h>

#include "GRRLIB.h"

using std::vector;

Bullet::Bullet() : col(RGB(1.0f, 1.0f, 1.0f))
{

}

Bullet::Bullet(double x, double y, double rot, const RGB &color, Entity *player) : col(color), owner(player), ttl(ticks_to_millisecs(gettime())+1500)
{
	position().X(x);
	position().Y(y);
	position().Rotation(rot);
	shape().Radius(5.0f);
}

Bullet::~Bullet()
{

}

bool Bullet::update()
{
	/* Collision Detection and barbaric treatment of CPU :( */
	// TODO COLLISION DETECTION
	
	position().translate(cos(position().Rotation()/180*M_PI)*3.5, sin(position().Rotation()/180*M_PI)*3.5);
	
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
	
	return (ticks_to_millisecs(gettime())<ttl);
}
void Bullet::render(GfxWrapper* gfx)
{
	gfx->drawRect(position().X()-shape().Radius(), 
					  position().Y()-shape().Radius(),
					  shape().Radius()*2, 
					  shape().Radius()*2, 
					  col);
}

Position &Bullet::position()
{
	return pos;
}
