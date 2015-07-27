#ifndef OPTIONSRENDERER_H
#define OPTIONSRENDERER_H

#include "renderer.h"

class OptionsRenderer : public Renderer
{
public:
	OptionsRenderer() : menu_sel(0)
	{
	}

	~OptionsRenderer()
	{
	}

	void setMenuSelection(int menuSelection);

    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const;

private:
	int menu_sel;
};

#endif // OPTIONSRENDERER_H
