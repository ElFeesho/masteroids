#include "renderers/pausedialogrenderer.h"
#include "pausedialog.h"

PauseDialog::PauseDialog(GamepadSource &gamepad, PauseDialogListener *listener)
        : gamepad(gamepad),
          listener(listener),
          pauseDialogRenderer(PauseDialogRenderer()),
          menu_sel(0)
{}

PauseDialog::~PauseDialog() {}

void PauseDialog::shown()
{
    gamepad.left().addDownHandler(&leftHandler);
    gamepad.right().addDownHandler(&rightHandler);
    gamepad.fire().addUpHandler(&fireHandler);
}

bool PauseDialog::update()
{
	return aliveMonitor().alive();
}

void PauseDialog::render(GfxWrapper &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}
