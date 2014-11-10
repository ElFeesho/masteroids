#include "bullet.h"

#include <ogc/lwp_watchdog.h>


Bullet::~Bullet()
{

}

bool Bullet::update()
{
	mover.move(position());
	
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
					  RGB::white);
}

