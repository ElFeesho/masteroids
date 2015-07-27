#ifndef RENDERER_H
#define RENDERER_H

#include "gfx/gfx.h"
#include "../position.h"
#include "../shape.h"
#include "../direction.h"

class Gfx;

class Renderer
{
public:
    virtual ~Renderer() {}

    virtual void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) const = 0;
};

#endif // RENDERER_H
