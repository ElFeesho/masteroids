#ifndef __MENURENDERER_H__
#define __MENURENDERER_H__

#include "gfx.h"
#include "renderer.h"
#include "asteroid_banner.h"
#include "font5.h"

class MenuRenderer : public Renderer 
{
public:
	MenuRenderer() : menu_sel(0) {}
	~MenuRenderer(){}
	
	void setMenuItemSelection(int selection)
	{
		menu_sel = selection;
	}
	
	void render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction)
	{
		gfx->drawRect(320-asteroid_banner_width/2,79,asteroid_banner_width+1, 310, RGB::blue);
		gfx->drawImg(321-asteroid_banner_width/2,80, asteroid_banner_width, asteroid_banner_height, asteroid_banner_data);
		gfx->drawImg(320, 200,controllers_width, controllers_height, controllers_data);
		int menuItemHeight = (font5_char_high+15);

		int menuSeparationHeight = 80 + asteroid_banner_height;
		int menuOffsetX = 320-asteroid_banner_width/2+20;

		if(menu_sel==0)
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight, "Start Game", RGB::yellow);
		}
		else
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight, "Start Game",RGB::white);
		}

		if(menu_sel==1)
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*2, "Options",RGB::yellow);
		}
		else
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*2, "Options",RGB::white);
		}

		if(menu_sel==2)
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*3, "About",RGB::yellow);
		}
		else
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*3, "About",RGB::white);
		}

		if(menu_sel == 3)
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*4, "Exit To HBC",RGB::yellow);
		}
		else
		{
			gfx->drawText(menuOffsetX, menuSeparationHeight+menuItemHeight*4, "Exit To HBC",RGB::white);
		}
		gfx->drawText(menuOffsetX, 80+asteroid_banner_height+(font5_char_high+10)*10, "Coded by Feesh! - gummybassist@gmail.com",RGB::white);
	}
	
private:
	int menu_sel;
};

#endif