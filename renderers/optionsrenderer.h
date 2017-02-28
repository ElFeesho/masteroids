#ifndef OPTIONSRENDERER_H
#define OPTIONSRENDERER_H

#include "renderer.h"

class OptionsRenderer : public Renderer
{
public:
	void setMenuSelection(int menuSelection);

    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const;

private:
	int menu_sel { 0 };
};

#endif // OPTIONSRENDERER_H
