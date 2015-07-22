#ifndef __MENURENDERER_H__
#define __MENURENDERER_H__

#include "../gfx/gfx.h"
#include "renderer.h"
#include "../images/asteroid_banner.h"
#include "../images/controllers.h"

class MenuRenderer : public Renderer
{
public:
	MenuRenderer() : menu_sel(0)
	{
	}

	~MenuRenderer()
	{
	}

	void setMenuItemSelection(int selection)
	{
		menu_sel = selection;
	}

    void render(GfxWrapper &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) const override
	{
        gfx.drawRect(320 - asteroid_banner_width / 2, 79, asteroid_banner_width + 1, 310, RGB::blue);
        gfx.drawImg(321 - asteroid_banner_width / 2, 80, asteroid_banner_width, asteroid_banner_height, asteroid_banner_data);
        gfx.drawImg(320, 200, controllers_width, controllers_height, controllers_data);
        int menuItemHeight = (gfx.textHeight() + 15);

		int menuSeparationHeight = 80 + asteroid_banner_height;
		int menuOffsetX = 320 - asteroid_banner_width / 2 + 80;

		if (menu_sel == 0)
		{
            gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight, "Start Game", RGB::yellow, CENTRE);
		}
		else
		{
            gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight, "Start Game", RGB::white, CENTRE);
		}

		if (menu_sel == 1)
		{
            gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight * 2, "Options", RGB::yellow, CENTRE);
		}
		else
		{
            gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight * 2, "Options", RGB::white, CENTRE);
		}

		if (menu_sel == 2)
		{
            gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight * 3, "About", RGB::yellow, CENTRE);
		}
		else
		{
            gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight * 3, "About", RGB::white, CENTRE);
		}

		if (menu_sel == 3)
		{
            gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight * 4, "Exit To HBC", RGB::yellow, CENTRE);
		}
		else
		{
            gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight * 4, "Exit To HBC", RGB::white, CENTRE);
		}
        gfx.drawText(false, 320, 80 + asteroid_banner_height + (gfx.textHeight() + 10) * 10, "Coded by Feesh! - gummybassist@gmail.com", RGB::white, TextAlignment::CENTRE);
	}

private:
	int menu_sel;
};

#endif
