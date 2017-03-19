#pragma once

#include <gfx/gfx.h>
#include <renderer.h>
#include "../images/asteroid_banner.h"
#include "../images/controllers.h"

class MenuRenderer : public Renderer
{
public:

	void setMenuItemSelection(int selection);

    void render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const override;

private:
	int menu_sel { 0 };
};
