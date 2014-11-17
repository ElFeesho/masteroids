#include "shiprenderer.h"

void ShipRenderer::render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) {
    double cx = position.X();
    double cy = position.Y();

    double tpx = position.X() + cos(direction.Angle()) * shape.Radius();
    double tpy = position.Y() + sin(direction.Angle()) * shape.Radius();

    double blx = position.X() + cos(direction.Angle() - M_PI * 0.75) * shape.Radius();
    double bly = position.Y() + sin(direction.Angle() - M_PI * 0.75) * shape.Radius();

    double brx = position.X() + cos(direction.Angle() + M_PI * 0.75) * shape.Radius();
    double bry = position.Y() + sin(direction.Angle() + M_PI * 0.75) * shape.Radius();

    gfx->drawLine(cx, cy, blx, bly, RGB::white);
    gfx->drawLine(cx, cy, brx, bry, RGB::white);

    gfx->drawLine(blx, bly, tpx, tpy, RGB::white);
    gfx->drawLine(brx, bry, tpx, tpy, RGB::white);
}