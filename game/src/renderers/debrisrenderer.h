#ifndef __DEBRIS_RENDERER_H__
#define __DEBRIS_RENDERER_H__

#include <renderer.h>
#include <gfx/gfx.h>

#include <cmath>

class DebrisRenderer : public Renderer {
public:
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &, RGB &colour = RGB::WHITE) const;
};

#endif
