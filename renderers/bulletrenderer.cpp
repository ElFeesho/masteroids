#include "renderers/bulletrenderer.h"

BulletRenderer::BulletRenderer()
{
}

BulletRenderer::~BulletRenderer()
{
}

void BulletRenderer::render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour) const
{
    gfx.drawRect(position.X() - shape.Radius(),
                 position.Y() - shape.Radius(),
                 shape.Radius() * 2,
                 shape.Radius() * 2,
                 colour);
}

