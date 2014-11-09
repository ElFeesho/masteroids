#include "options.h"

#include <cstdio>

#include <ogcsys.h>
#include <gccore.h>

#include <ogc/lwp_watchdog.h>

#include <string.h>

#include "controlconf.h"

#include "font5.h"
#include "GRRLIB.h"
#include "options_img.h"
#include "gamepadinputmanager.h"
#include "music.h"

using std::sprintf;

Options::Options(OptionsListener *listener) : listener(listener), alive(true), menu_sel(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1), child(NULL), colour(RGB(1.0f, 1.0f, 1.0f)), colourHighlight(RGB(1.0f, 0.8f, 0.0f))
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

Options::~Options()
{
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

bool Options::update()
{
	if(child!=NULL)
	{
		if(!child->update())
		{
			delete child;
			child = NULL;
		}
		return true;
	}

	
	return alive;
}

void Options::render(GfxWrapper* gfx) 
{
	gfx->drawRect(120, 80, 403, 340, RGB::blue);
	gfx->drawImg(321-options_width/2,81,options_width, options_height, options_img);
	
	char lives[32] = { 0 };
	char diff[64] = { 0 };
	char tk[32] = { 0 };
	char players_txt[32] = { 0 };
	char max_bulls[32] = { 0 };
	char muse[32] = { 0 };
	
	sprintf(lives, "Lives: %d",Options::lives);
	sprintf(diff,  "Difficulty: %-6s",(Options::difficulty==0)?("Easy"):((Options::difficulty==1)?("Medium"):("Hard")));
	sprintf(tk,    "Team Killing: %-3s",(Options::team_kill)?("Yes"):("No"));
	sprintf(players_txt, "Players: %d",Options::players);
	sprintf(max_bulls,   "Max Bullets: %-2d",Options::max_bullets);
	sprintf(muse, "Enable Music: %-3s",(Options::music)?("Yes"):("No"));

	if(menu_sel == 0)
	{
		gfx->drawText((640-strlen(lives)*font5_char_width)/2, 80+font5_char_high*8, lives,colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen(lives)*font5_char_width)/2, 80+font5_char_high*8, lives,colour);
	}
	
	if(menu_sel == 1)
	{
		gfx->drawText((640-strlen(diff)*font5_char_width)/2, 80+font5_char_high*11, diff,colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen(diff)*font5_char_width)/2, 80+font5_char_high*11, diff,colour);
	}
	
	if(menu_sel == 2)
	{
		gfx->drawText((640-strlen(tk)*font5_char_width)/2, 80+font5_char_high*14, tk,colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen(tk)*font5_char_width)/2, 80+font5_char_high*14, tk,colour);
	}
	
	if(menu_sel == 3)
	{
		gfx->drawText((640-strlen(players_txt)*font5_char_width)/2, 80+font5_char_high*17, players_txt,colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen(players_txt)*font5_char_width)/2, 80+font5_char_high*17, players_txt,colour);
	}
	
	if(menu_sel == 4)
	{
		gfx->drawText((640-strlen(max_bulls)*font5_char_width)/2, 80+font5_char_high*20, max_bulls,colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen(max_bulls)*font5_char_width)/2, 80+font5_char_high*20, max_bulls,colour);
	}
	
	if(menu_sel == 5)
	{
		gfx->drawText((640-strlen(muse)*font5_char_width)/2, 80+font5_char_high*23, muse,colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen(muse)*font5_char_width)/2, 80+font5_char_high*23, muse,colour);
	}
	
	if(menu_sel == 6)
	{
		gfx->drawText((640-strlen("Configure Controls")*font5_char_width)/2, 80+font5_char_high*26, "Configure Controls",colourHighlight);
	}
	else
	{
		gfx->drawText((640-strlen("Configure Controls")*font5_char_width)/2, 80+font5_char_high*26, "Configure Controls",colour);
	}
	
	gfx->drawText((640-13*font5_char_width)/2, 80+font5_char_high*29, "Start to Exit",colour);
}


void Options::buttonDown(GamepadButton button)
{
	unsigned long cticks = ticks_to_millisecs(gettime());
	
	if(button == BUTTON_UP)
	{
		ldir = 0;
		if(menu_sel>0)
			menu_sel--;
		next_change = ticks_to_millisecs(gettime()) + 500;
	}
	if(button == BUTTON_DOWN)
	{
		ldir = 1;
	
		if(menu_sel<6)
			menu_sel++;

		next_change = ticks_to_millisecs(gettime()) + 500;
	}
	
	if (button == BUTTON_LEFT)
	{
		if(ldir==2)
			next_change = cticks+200;
		else
			next_change = cticks+500;
		ldir = 2;
		switch(menu_sel)
		{
			case 0: // Lives
				if(Options::lives>1)
					Options::lives--;
				break;
			case 1: // Difficulty
				if(Options::difficulty>0)
					Options::difficulty--;
				break;
			case 2: // Team killing
				Options::team_kill = false;
				break;
			case 3: // Players
				if(Options::players>1)
					Options::players--;
				break;
			case 4: // Max Bullets
				if(Options::max_bullets>1)
					Options::max_bullets--;
				break;
			case 5: // Music
				Options::music = false;
				break;
		}
	}

	if (button == BUTTON_RIGHT)
	{
		if(ldir==3)
			next_change = cticks+200;
		else
			next_change = cticks+500;
		ldir = 3;

		switch(menu_sel)
		{
			case 0: // Lives
				if(Options::lives<9)
					Options::lives++;
				break;
			case 1: // Difficulty
				if(Options::difficulty<2)
					Options::difficulty++;
				break;
			case 2: // Team killing
				if(!Options::team_kill)
					Options::team_kill = true;
				break;
			case 3: // Players
				if(Options::players<4)
					Options::players++;
				break;
			case 4: // Max Bullets
				if(Options::max_bullets<10)
					Options::max_bullets++;
				break;
			case 5: // Music
				Options::music = true;
				break;
		}
	}
	
	if(button == BUTTON_FIRE)
	{
		if(menu_sel == 6)
		{
			//child = new ControlConf();
			listener->optionsControllerConfigSelected();
		}
	}

}

void Options::buttonUp(GamepadButton button)
{
	next_change = 0;
	ldir = -1;
	
	if(button == BUTTON_START)
	{
		listener->optionsMenuClosed();
	}
}


int Options::lives = 3;
int Options::difficulty = 1;
bool Options::team_kill = false;
int Options::players = 1;
int Options::max_bullets = 5;
bool Options::music = false;
