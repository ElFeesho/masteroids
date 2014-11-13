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

Ship::Ship(Gamepad *gamepad, ShipListener *listener) : shipRenderer(ShipRenderer()), mover(ShipMover()), bodyShape(Shape(10.0f)), gamepad(gamepad), listener(listener), colour(RGB(0.0f, 0.0f, 0.0f)), rotationSpeed(0), kill_time(0), travelDirection(Direction(0.0, 0.0))
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

Gamepad* Ship::getGamepad()
{
	return gamepad;
}

void Ship::render(GfxWrapper* gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}


