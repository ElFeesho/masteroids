#include <iostream>
#include "renderers/pausedialogrenderer.h"
#include "pausedialog.h"

PauseDialog::PauseDialog(GamepadSource &ngamepad, PauseDialogListener *nlistener)
        : gamepad(ngamepad),
          listener(nlistener)
{
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

Position &PauseDialog::position()
{
  return Position::NONE;
}

Shape &PauseDialog::shape()
{
  return Shape::NONE;
}

Direction &PauseDialog::direction()
{
  return Direction::NONE;
}

const AliveMonitor & PauseDialog::aliveMonitor()
{
      return alwaysAliveMonitor;
}

const Renderer & PauseDialog::renderer()
{
  return pauseDialogRenderer;
}

void PauseDialog::reset() {
    highlightMenu(0);
}

void PauseDialog::highlightMenu(int menuSelection) {
    menu_sel = menuSelection;
    pauseDialogRenderer.setMenuSelection(menu_sel);
}