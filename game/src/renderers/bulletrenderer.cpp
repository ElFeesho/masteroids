#include "renderers/bulletrenderer.h"

void BulletRenderer::render(Gfx &gfx, Position &position, Shape &shape, Direction &, RGB &colour) const
{
    gfx.drawRect(position.X() - shape.Radius(),
                 position.Y() - shape.Radius(),
                 shape.Radius(),
                 shape.Radius(),
                 colour);
}
