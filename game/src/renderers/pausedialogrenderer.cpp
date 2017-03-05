#include "pausedialogrenderer.h"

void PauseDialogRenderer::setMenuSelection(int menuSelection)
{
	menu_sel = menuSelection;
}

void PauseDialogRenderer::render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const
{
	static int titleWidth = gfx.measureText("Quit Current Game?").w;

	int dialogWidth = 400;
	int dialogHeight = 100;
    gfx.drawRect((640 - dialogWidth)/2, (480 - dialogHeight)/2, dialogWidth, dialogHeight, RGB::BLUE);

    gfx.drawText(false, (640 - titleWidth)/2, (480 - dialogHeight)/2, "Quit Current Game?", RGB::WHITE);

	if (menu_sel == 0)
	{
        gfx.drawText(false, (640 - 280)/2, 240 - 5, "Continue", RGB::YELLOW);
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
