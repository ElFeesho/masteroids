#ifndef __DEBRIS_RENDERER_H__
#define __DEBRIS_RENDERER_H__

#include "renderer.h"
#include <gfx/gfx.h>

class DebrisRenderer : public Renderer
{
public:
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &, RGB &colour = RGB::WHITE) const
	{
        gfx.drawLine(position.X() - cos(position.Rotation()) * shape.Radius(),
				position.Y() - sin(position.Rotation()) * shape.Radius(),
				position.X() + cos(position.Rotation()) * shape.Radius(),
				position.Y() + sin(position.Rotation()) * shape.Radius(),
				colour);
	}
};

#endif
