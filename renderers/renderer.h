#ifndef RENDERER_H
#define RENDERER_H

#include <gfx/gfx.h>
#include "../position.h"
#include "../shape.h"
#include "../direction.h"

class GfxWrapper;

class Renderer {
public:
    virtual ~Renderer() {
    }

    virtual void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) = 0;
};

#endif // RENDERER_H
