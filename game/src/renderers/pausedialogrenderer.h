#ifndef __INGAMEMENURENDERER_H__
#define __INGAMEMENURENDERER_H__

#include "renderer.h"

class Gfx;

class PauseDialogRenderer : public Renderer
{
public:
	PauseDialogRenderer();

	~PauseDialogRenderer();

	void setMenuSelection(int menuSelection);

    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const override;

private:
	int menu_sel;
};

#endif
