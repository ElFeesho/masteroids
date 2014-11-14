#include <gccore.h>
#include <ogc/lwp_watchdog.h>
#include <stdio.h>
#include <stdlib.h>
#include <ogcsys.h>

#include <math.h>

#include "ship.h"
#include "movers/shipmover.h"

Ship::Ship(Gamepad *gamepad, ShipListener *listener, ShipMover &shipMover) : visible(true), shipRenderer(ShipRenderer()), mover(shipMover), bodyShape(Shape(10.0f)), gamepad(gamepad), listener(listener), rotationSpeed(0), travelDirection(Direction(0.0, 0.0))
{
	gamepad->addListener(this);
	shape().Radius(10);
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
	return aliveMonitor().alive();
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
	if(isVisible())
	{
		renderer().render(gfx, position(), shape(), direction());
	}
}


