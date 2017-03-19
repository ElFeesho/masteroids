#include "renderers/bulletrenderer.h"

void BulletRenderer::render(Gfx &gfx, Position &position, Shape &shape, Direction &, RGB &colour) const {
    gfx.drawRect((int) (position.X() - shape.Radius()),
                 (int) (position.Y() - shape.Radius()),
                 (int) shape.Radius(),
                 (int) shape.Radius(),
                 colour);
}

