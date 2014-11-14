#ifndef __SHIPRENDERER_H__
#define __SHIPRENDERER_H__

#include "renderer.h"
#include "gfx/gfx.h"

class ShipRenderer : public Renderer
{
public:
	void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction);
};

#endif