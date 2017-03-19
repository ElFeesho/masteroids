#include "debrisrenderer.h"

void DebrisRenderer::render(Gfx &gfx, Position &position, Shape &shape, Direction &, RGB &colour) const {
    gfx.drawLine((int) (position.X() - cos(position.Rotation()) * shape.Radius()),
                 (int) (position.Y() - sin(position.Rotation()) * shape.Radius()),
                 (int) (position.X() + cos(position.Rotation()) * shape.Radius()),
                 (int) (position.Y() + sin(position.Rotation()) * shape.Radius()),
                 colour);
}
