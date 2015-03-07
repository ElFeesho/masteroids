#ifndef __DEBRIS_RENDERER_H__
#define __DEBRIS_RENDERER_H__

#include "renderer.h"
#include "../gfx/gfx.h"

class DebrisRenderer : public Renderer
{
public:
	void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white)
	{
		gfx->drawLine(position.X() - cos(position.Rotation()) * shape.Radius(),
				position.Y() - sin(position.Rotation()) * shape.Radius(),
				position.X() + cos(position.Rotation()) * shape.Radius(),
				position.Y() + sin(position.Rotation()) * shape.Radius(),
				colour);
	}
};

#endif