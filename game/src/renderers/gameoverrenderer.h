#pragma once

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include "renderer.h"

class GameOverRenderer : public Renderer
{
public:
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const override;
};
