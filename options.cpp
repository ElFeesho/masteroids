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

#include "music.h"

using std::sprintf;

Options::Options() : menu_sel(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1), child(NULL)
{

}

Options::~Options()
{

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
	
	unsigned long cticks = ticks_to_millisecs(gettime());

	/* Prevent the nunchuk from flying through menu options */
	if(ControlConf::button_held(0,BUTTON_UP) && cticks>next_change)
	{
		if(ldir==0)
			next_change = cticks+200;
		else
			next_change = cticks+500;
		ldir = 0;
		if(menu_sel>0)
			menu_sel--;
	}

	if(ControlConf::button_held(0,BUTTON_DOWN) && cticks>next_change)
	{
		if(ldir==1)
			next_change = cticks+200;
		else
			next_change = cticks+500;
		ldir = 1;
		if(menu_sel<6)
			menu_sel++;
	}
	
	/* Allow the user to push the buttons over and over quickly :D */
	if(!ControlConf::button_held(0,BUTTON_UP) && ldir == 0)
	{
		next_change = 0;
	}

	if(!ControlConf::button_held(0,BUTTON_DOWN) && ldir == 1)
	{
		next_change = 0;
	}

	if(!ControlConf::button_held(0,BUTTON_LEFT) && ldir == 2)
	{
		next_change = 0;
	}

	if(!ControlConf::button_held(0,BUTTON_RIGHT) && ldir == 3)
	{
		next_change = 0;
	}

	if(ControlConf::button_down(0,BUTTON_START))
	{
		return false;
	}
	
	if(ControlConf::button_held(0,BUTTON_LEFT) && cticks>next_change)
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
	
	if(ControlConf::button_held(0,BUTTON_RIGHT) && cticks>next_change)
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
	
	GRRLIB_DrawRectangle(120,80,340, 403, 0x001f,0);
	GRRLIB_DrawImg(321-options_width/2,81,options_width, options_height, options_img, 0.0, 1.0);

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
		GRRLIB_Print((640-strlen(lives)*font5_char_width)/2, 80+font5_char_high*8, font5_char_width, font5_char_high, lives,font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen(lives)*font5_char_width)/2, 80+font5_char_high*8, font5_char_width, font5_char_high, lives,font5, 0xffff, 0x0000);
	
	if(menu_sel == 1)
		GRRLIB_Print((640-strlen(diff)*font5_char_width)/2, 80+font5_char_high*11, font5_char_width, font5_char_high, diff,font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen(diff)*font5_char_width)/2, 80+font5_char_high*11, font5_char_width, font5_char_high, diff,font5, 0xffff, 0x0000);
		
	if(menu_sel == 2)
		GRRLIB_Print((640-strlen(tk)*font5_char_width)/2, 80+font5_char_high*14, font5_char_width, font5_char_high, tk,font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen(tk)*font5_char_width)/2, 80+font5_char_high*14, font5_char_width, font5_char_high, tk,font5, 0xffff, 0x0000);
		
	if(menu_sel == 3)
		GRRLIB_Print((640-strlen(players_txt)*font5_char_width)/2, 80+font5_char_high*17, font5_char_width, font5_char_high, players_txt,font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen(players_txt)*font5_char_width)/2, 80+font5_char_high*17, font5_char_width, font5_char_high, players_txt,font5, 0xffff, 0x0000);

	if(menu_sel == 4)	
		GRRLIB_Print((640-strlen(max_bulls)*font5_char_width)/2, 80+font5_char_high*20, font5_char_width, font5_char_high, max_bulls,font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen(max_bulls)*font5_char_width)/2, 80+font5_char_high*20, font5_char_width, font5_char_high, max_bulls,font5, 0xffff, 0x0000);

	if(menu_sel == 5)	
		GRRLIB_Print((640-strlen(muse)*font5_char_width)/2, 80+font5_char_high*23, font5_char_width, font5_char_high, muse,font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen(muse)*font5_char_width)/2, 80+font5_char_high*23, font5_char_width, font5_char_high, muse,font5, 0xffff, 0x0000);

	if(menu_sel == 6)	
		GRRLIB_Print((640-strlen("Configure Controls")*font5_char_width)/2, 80+font5_char_high*26, font5_char_width, font5_char_high, (char*)"Configure Controls",font5, 0xffa0, 0x0000);
	else
		GRRLIB_Print((640-strlen("Configure Controls")*font5_char_width)/2, 80+font5_char_high*26, font5_char_width, font5_char_high, (char*)"Configure Controls",font5, 0xffff, 0x0000);

	GRRLIB_Print((640-13*font5_char_width)/2, 80+font5_char_high*29, font5_char_width, font5_char_high, (char*)"Start to Exit",font5, 0xffff, 0x0000);
	
	if(ControlConf::button_down(0,BUTTON_SHOOT))
	{
		if(menu_sel == 6)
		{
			child = new ControlConf();
			return true;
		}
	}
		
	return true;
}

int Options::lives = 3;
int Options::difficulty = 1;
bool Options::team_kill = false;
int Options::players = 1;
int Options::max_bullets = 5;
bool Options::music = false;
