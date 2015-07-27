#pragma once

#include "../gfx/gfx.h"
#include "renderer.h"

class BulletRenderer : public Renderer
{
public:
    BulletRenderer();

    ~BulletRenderer();

    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const;
};


