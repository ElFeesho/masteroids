#include <renderers/pausedialogrenderer.h>
#include "pausedialog.h"

PauseDialog::PauseDialog(Gamepad *gamepad, PauseDialogListener *listener)
		: pauseDialogRenderer(PauseDialogRenderer()), gamepad(gamepad), listener(listener), menu_sel(0)
{
	gamepad->addListener(this);
}

PauseDialog::~PauseDialog()
{
	gamepad->removeListener(this);
}

bool PauseDialog::update()
{
	return aliveMonitor().alive();
}

void PauseDialog::render(GfxWrapper *gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

bool PauseDialog::buttonDown(GamepadButton button)
{
	if (button == BUTTON_LEFT)
	{
		menu_sel = 0;
	}
	else if (button == BUTTON_RIGHT)
	{
		menu_sel = 1;
	}
	pauseDialogRenderer.setMenuSelection(menu_sel);
	return false;
}

bool PauseDialog::buttonUp(GamepadButton button)
{
	if (button == BUTTON_FIRE || button == BUTTON_START)
	{
		if (menu_sel == 0)
		{
			listener->ingameContinueSelected();
		}
		else
		{
			listener->ingameQuitSelected();
		}
		return true;
	}
	return false;
}
