#include "ingamemenurenderer.h"

InGameMenuRenderer::InGameMenuRenderer() : menu_sel(0)
{
}

InGameMenuRenderer::~InGameMenuRenderer()
{
}

void InGameMenuRenderer::setMenuSelection(int menuSelection)
{
	menu_sel = menuSelection;
}

void InGameMenuRenderer::render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour)
{
	gfx->drawRect((320 - 150), 240 - 50, 300, 90, RGB::blue);

	gfx->drawText(320 - 80, 240 - 40, "Quit Current Game?", RGB::white);
	if (menu_sel == 0)
	{
		gfx->drawText(320 - 140, 240 - 5, "Continue", RGB::yellow);
	}
	else
	{
		gfx->drawText(320 - 140, 240 - 5, "Continue", RGB::white);
	}

	if (menu_sel == 1)
	{
		gfx->drawText(420, 240 - 5, "Exit", RGB::yellow);
	}
	else
	{
		gfx->drawText(420, 240 - 5, "Exit", RGB::white);
	}
}