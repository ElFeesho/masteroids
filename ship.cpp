#include <gccore.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <ogcsys.h>

#include <math.h>

#include "GRRLIB.h"

#include "font5.h"

#include "ship.h"
#include "asteroid.h"
#include "engine.h"
#include "bullet.h"
#include "options.h"
#include "ingame.h"
#include "debrisfragment.h"

Ship::Ship(Gamepad *gamepad, ShipListener *listener) : mover(ShipMover()), gamepad(gamepad), listener(listener), colour(RGB(0.0f, 0.0f, 0.0f)), rotationSpeed(0), kill_time(0), travelDirection(Direction(0.0, 0.0))
{
	gamepad->addListener(this);
	shape().Radius(7.5);
	colour = RGB(0.0f, 1.0f, 0.0f);
	position().X(640/4);
	position().Y(480/4);
}

Ship::~Ship()
{
  gamepad->removeListener(this);
}

bool Ship::update()
{
	travelDirection.rotate(Time::factorTime(rotationSpeed));
	mover.move(direction(), position());

	if(position().X()>640.0+10.0)
	{
		position().X(-10.0);
	}
	if(position().X()<0.0-10.0)
	{
		position().X(640.0+10.0);
	}

	if(position().Y()>480.0+10.0)
	{
		position().Y(-10.0);
	}

	if(position().Y()<0.0-10.0)
	{
		position().Y(480.0+10.0);
	}

	return true;
}

void Ship::buttonDown(GamepadButton button)
{
  if(button == BUTTON_RIGHT)
  {
	 rotationSpeed = 0.1f;
  }
  else if(button == BUTTON_LEFT)
  {
	 rotationSpeed = -0.1f;
  }
  else if(button == BUTTON_UP)
  {
	  travelDirection.Speed(0.1f);
  }
  else if(button == BUTTON_FIRE)
  {
	  listener->shipFired(this);
  }
  else if(button == BUTTON_START)
  {
	  listener->shipRequestedPause(this);
  }
}

void Ship::buttonUp(GamepadButton button)
{
  if(button == BUTTON_LEFT || button == BUTTON_RIGHT)
  {
	 rotationSpeed = 0;
  }
  else if(button == BUTTON_UP)
  {
	 travelDirection.Speed(0.0f);
  }
}

void Ship::on_hit()
{
	kill_time = ticks_to_millisecs(gettime());
	//get_engine()->add_entity(new Debris(3, X(), Y(), rot, xspeed, yspeed, colour, 2500));
	/* Make sure the ship doesn't get hit into by other entities whilst it's disappeared */
	position().X(-500.0);
	position().Y(-500.0);
}

Gamepad* Ship::getGamepad()
{
	return gamepad;
}

void Ship::render(GfxWrapper* gfx)
{
	double tp_x = position().X()+cos(travelDirection.Angle())*10.0;
	double tp_y = position().Y()+sin(travelDirection.Angle())*10.0;
	double br_x = position().X()+cos((travelDirection.Angle())+2.09)*6;
	double bl_x = position().X()+cos((travelDirection.Angle())+4.18)*6;
	double br_y = position().Y()+sin((travelDirection.Angle())+2.09)*6;
	double bl_y = position().Y()+sin((travelDirection.Angle())+4.18)*6;

	gfx->drawLine(tp_x, tp_y, br_x, br_y, colour);
	gfx->drawLine(tp_x, tp_y, bl_x, bl_y, colour);
	gfx->drawLine(br_x, br_y, position().X(), position().Y(), colour);
	gfx->drawLine(bl_x, bl_y, position().X(), position().Y(), colour);
}


