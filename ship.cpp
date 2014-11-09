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
#include "debris.h"

Ship::Ship(Gamepad *gamepad, ShipListener *listener) : gamepad(gamepad), listener(listener), player_num(1), colour(RGB(0.0f, 0.0f, 0.0f)), rot(90*180), xspeed(0), yspeed(0), rotationSpeed(0), propulsion(0), bullets_fired(0), score(0), llevel(1), lives(Options::lives), kill_time(0)
{
  gamepad->addListener(this);
	set_radius(7.5);
  colour = RGB(0.0f, 1.0f, 0.0f);
	position().X(640/4);
	position().Y(480/4);
}

Ship::Ship(int padnum) : player_num(padnum), rot(90+(padnum%2)*180), xspeed(0), yspeed(0), rotationSpeed(0), propulsion(0), bullets_fired(0), score(0), llevel(1), lives(Options::lives), kill_time(0), colour(RGB(0.0f, 0.0f,0.0f))
{
	scores[player_num] = 0;
	set_radius(7.5);
	/* Hardcoded X and Y positions for players */
	if(player_num == 0)
	{
		Ship::players[0] = this;
		colour = RGB(0.0f, 1.0f, 0.0f);
		position().X(640/4);
		position().Y(480/4);
	}
	if(player_num == 1)
	{
		Ship::players[1] = this;
		colour = RGB(1.0f, 1.0f, 0.0f);
		position().X(640/4*3);
		position().Y(480/4*3);
	}
	if(player_num == 2)
	{
		Ship::players[2] = this;
		colour = RGB(0.0f, 0.0f, 1.0f);
		position().X(640/4*3);
		position().Y(480/4);
	}
	if(player_num == 3)
	{
		Ship::players[3] = this;
		colour = RGB(0.0f, 0.5f, 1.0f);
		position().X(640/4);
		position().Y(480/4*3);
	}
}

Ship::~Ship()
{
  gamepad->removeListener(this);
}

void Ship::inc_bfired()
{
	bullets_fired++;
}

void Ship::dec_bfired()
{
	bullets_fired--;
}

bool Ship::update()
{
	//draw_lives(gfx);

	if(lives<=0) // Game over man - Engine checks to see whether game over screen should be shown
		return true;

	if(kill_time!=0) /* Whilst 'dead' kill time will be time of death */
	{
		if(ticks_to_millisecs(gettime())>kill_time+2500) /* Player is dead for 2.5 seconds */
		{
			double px = 0, py = 0;
			if(player_num == 0)
		   {
				px = 640/4;
				py = 480/4;
			}
			else if(player_num == 1)
			{
				px = 640/4*3;
				py = 480/4*3;
			}
			else if(player_num == 2)
			{
				px = 640/4*3;
				py = 480/4;
			}
			else if(player_num == 3)
			{
				px = 640/4;
				py = 480/4*3;
			}

			xspeed = 0;
			yspeed = 0;
			rot = 90+(player_num%2)*180;

			
		}
		return true;
	}

	rot += rotationSpeed;
	xspeed += cos(rot/180*M_PI)*propulsion;
	yspeed += sin(rot/180*M_PI)*propulsion;
	
	position().translate(xspeed, yspeed);

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

	/* Collision Detection and barbaric treatment of CPU :( 
	for(vector<Collobj *>::iterator iter = get_engine()->get_collents()->begin(); iter!=get_engine()->get_collents()->end(); iter++)
	{
		if(!Options::team_kill) // Bumping into each other causes big BOOM :D
		{
			if((*iter) == Ship::players[0]||(*iter) == Ship::players[1]||(*iter) == Ship::players[2]||(*iter) == Ship::players[3])
				continue;
		}
		if((*iter)==this)
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
				this->on_hit();
				return true;
			}
	 	}
	}*/

	return true;
}

void Ship::draw_lives(GfxWrapper *gfx)
{
	/*char score_buf[32] = { 0 };
	char lives_buf[10] = { 0 };
	sprintf(score_buf, "Score: %d",score);
	sprintf(lives_buf, "x %d", lives);
	if(player_num == 0)
	{
		gfx->drawText(35, 35, score_buf,colour);
		gfx->drawText(65,48,lives_buf, colour);
		gfx->drawLine(15+40, 50, 15+35, 60, colour);
		gfx->drawLine(15+40, 50, 15+45, 60, colour);
		gfx->drawLine(15+35, 60, 15+40, 55, colour);
		gfx->drawLine(15+45, 60, 15+40, 55, colour);
	}
	if(player_num == 1)
	{
		gfx->drawText(490, 435, score_buf,colour);
		gfx->drawText(520,448,lives_buf, colour);
		gfx->drawLine(15+495, 450, 15+490, 460, colour);
		gfx->drawLine(15+495, 450, 15+500, 460, colour);
		gfx->drawLine(15+490, 460, 15+495, 455, colour);
		gfx->drawLine(15+500, 460, 15+495, 455, colour);
	}
	if(player_num == 2)
	{
		gfx->drawText(490, 35, score_buf,colour);
		gfx->drawText(520,48,lives_buf, colour);
		gfx->drawLine(15+495, 50, 15+490, 60, colour);
		gfx->drawLine(15+495, 50, 15+500, 60, colour);
		gfx->drawLine(15+490, 60, 15+495, 55, colour);
		gfx->drawLine(15+500, 60, 15+495, 55, colour);
	}
	if(player_num == 3)
	{
		gfx->drawText(35, 435, score_buf,colour);
		gfx->drawText(65,448,lives_buf, colour);
		gfx->drawLine(15+40, 450, 15+35, 460, colour);
		gfx->drawLine(15+40, 450, 15+45, 460, colour);
		gfx->drawLine(15+35, 460, 15+40, 455, colour);
		gfx->drawLine(15+45, 460, 15+40, 455, colour);
	}
	*/
}

int Ship::get_lives()
{
	return lives;
}

int Ship::get_score()
{
	return score;
}

void Ship::add_score(int am)
{
	score+=am;
	if(score>llevel*500+(Options::difficulty*500))
	{
		// New life!
		lives++;
		llevel++;
	}
	scores[player_num] = score;
}

void Ship::buttonDown(GamepadButton button)
{
  if(button == BUTTON_RIGHT)
  {
	 rotationSpeed = 5.5f;
  }
  else if(button == BUTTON_LEFT)
  {
	 rotationSpeed = -5.5f;
  }
  else if(button == BUTTON_UP)
  {
	 propulsion = 0.1f;
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
	 propulsion = 0;
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
	double tp_x = position().X()+cos(rot/180*M_PI)*10.0;
	double tp_y = position().Y()+sin(rot/180*M_PI)*10.0;
	double br_x = position().X()+cos((rot/180*M_PI)+2.09)*6;
	double bl_x = position().X()+cos((rot/180*M_PI)+4.18)*6;
	double br_y = position().Y()+sin((rot/180*M_PI)+2.09)*6;
	double bl_y = position().Y()+sin((rot/180*M_PI)+4.18)*6;

	gfx->drawLine(tp_x, tp_y, br_x, br_y, colour);
	gfx->drawLine(tp_x, tp_y, bl_x, bl_y, colour);
	gfx->drawLine(br_x, br_y, position().X(), position().Y(), colour);
	gfx->drawLine(bl_x, bl_y, position().X(), position().Y(), colour);
}

Ship *Ship::players[4] = { NULL };
int Ship::scores[4] = { 0 };
