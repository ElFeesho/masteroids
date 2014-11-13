#include "optionsrenderer.h"
#include "options.h"
#include "options_img.h"
#include "font5.h"

void OptionsRenderer::setMenuSelection(int menuSelection)
{
	menu_sel = menuSelection;
}

void OptionsRenderer::render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
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
		gfx->drawText((640-strlen(lives)*font5_char_width)/2, 80+font5_char_high*8, lives, RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen(lives)*font5_char_width)/2, 80+font5_char_high*8, lives,RGB::white);
	}
	
	if(menu_sel == 1)
	{
		gfx->drawText((640-strlen(diff)*font5_char_width)/2, 80+font5_char_high*11, diff,RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen(diff)*font5_char_width)/2, 80+font5_char_high*11, diff,RGB::white);
	}
	
	if(menu_sel == 2)
	{
		gfx->drawText((640-strlen(tk)*font5_char_width)/2, 80+font5_char_high*14, tk,RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen(tk)*font5_char_width)/2, 80+font5_char_high*14, tk,RGB::white);
	}
	
	if(menu_sel == 3)
	{
		gfx->drawText((640-strlen(players_txt)*font5_char_width)/2, 80+font5_char_high*17, players_txt,RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen(players_txt)*font5_char_width)/2, 80+font5_char_high*17, players_txt,RGB::white);
	}
	
	if(menu_sel == 4)
	{
		gfx->drawText((640-strlen(max_bulls)*font5_char_width)/2, 80+font5_char_high*20, max_bulls,RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen(max_bulls)*font5_char_width)/2, 80+font5_char_high*20, max_bulls,RGB::white);
	}
	
	if(menu_sel == 5)
	{
		gfx->drawText((640-strlen(muse)*font5_char_width)/2, 80+font5_char_high*23, muse,RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen(muse)*font5_char_width)/2, 80+font5_char_high*23, muse,RGB::white);
	}
	
	if(menu_sel == 6)
	{
		gfx->drawText((640-strlen("Configure Controls")*font5_char_width)/2, 80+font5_char_high*26, "Configure Controls",RGB::yellow);
	}
	else
	{
		gfx->drawText((640-strlen("Configure Controls")*font5_char_width)/2, 80+font5_char_high*26, "Configure Controls",RGB::white);
	}
	
	gfx->drawText((640-13*font5_char_width)/2, 80+font5_char_high*29, "Start to Exit",RGB::white);
}
