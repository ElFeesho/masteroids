#include "pausedialogrenderer.h"

void PauseDialogRenderer::setMenuSelection(int menuSelection)
{
	menu_sel = menuSelection;
}

void PauseDialogRenderer::render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const
{
    gfx.drawRect((320 - 150), 240 - 50, 300, 90, RGB::BLUE);

    gfx.drawText(false, 320 - 80, 240 - 40, "Quit Current Game?", RGB::WHITE);
	if (menu_sel == 0)
	{
        gfx.drawText(false, 320 - 140, 240 - 5, "Continue", RGB::YELLOW);
	}
	else
	{
        gfx.drawText(false, 320 - 140, 240 - 5, "Continue", RGB::WHITE);
	}

	if (menu_sel == 1)
	{
        gfx.drawText(false, 420, 240 - 5, "Exit", RGB::YELLOW);
	}
	else
	{
        gfx.drawText(false, 420, 240 - 5, "Exit", RGB::WHITE);
	}
}
