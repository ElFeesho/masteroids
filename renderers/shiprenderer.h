#ifndef __SHIPRENDERER_H__
#define __SHIPRENDERER_H__

#include "renderer.h"
#include "../gfx/gfx.h"

class ShipRenderer : public Renderer
{
public:
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) const;
};

#endif
