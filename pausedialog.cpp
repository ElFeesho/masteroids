#include <renderers/pausedialogrenderer.h>
#include "pausedialog.h"

PauseDialog::PauseDialog(GamepadSource &gamepad, PauseDialogListener *listener)
		: pauseDialogRenderer(PauseDialogRenderer()), gamepad(gamepad), listener(listener), menu_sel(0)
{

	gamepad.left().addDownHandler(&leftHandler);
	gamepad.right().addDownHandler(&rightHandler);
	gamepad.fire().addUpHandler(&fireHandler);
}

PauseDialog::~PauseDialog()
{
	gamepad.left().removeDownHandler(&leftHandler);
	gamepad.right().removeDownHandler(&rightHandler);
	gamepad.fire().removeUpHandler(&fireHandler);
}

bool PauseDialog::update()
{
	return aliveMonitor().alive();
}

void PauseDialog::render(GfxWrapper *gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}