#include <iostream>
#include "renderers/pausedialogrenderer.h"
#include "pausedialog.h"

PauseDialog::PauseDialog(GamepadSource &ngamepad, PauseDialogListener *nlistener)
        : gamepad(ngamepad),
          listener(nlistener),
          pauseDialogRenderer(),
          menu_sel(0)
{
    std::cout << "PauseDialog::CTOR" << std::endl;
}

PauseDialog::~PauseDialog() {
    std::cout << "PauseDialog::DTOR" << std::endl;
}

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

void PauseDialog::render(Gfx &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

void PauseDialog::reset() {
    highlightMenu(0);
}

void PauseDialog::highlightMenu(int menuSelection) {
    menu_sel = menuSelection;
    pauseDialogRenderer.setMenuSelection(menu_sel);
}