#include <Tcl/tcl.h>
#include "shiprenderer.h"

static void renderAt(GfxWrapper *gfx, double x, double y, double radius, double rotation)
{
    double cx = x;
    double cy = y;

    double tpx = cx + cos(rotation) * radius;
    double tpy = cy + sin(rotation) * radius;

    double blx = cx + cos(rotation - M_PI * 0.75) * radius;
    double bly = cy + sin(rotation - M_PI * 0.75) * radius;

    double brx = cx + cos(rotation + M_PI * 0.75) * radius;
    double bry = cy + sin(rotation + M_PI * 0.75) * radius;

    gfx->drawLine(cx, cy, blx, bly, RGB::white);
    gfx->drawLine(cx, cy, brx, bry, RGB::white);

    gfx->drawLine(blx, bly, tpx, tpy, RGB::white);
    gfx->drawLine(brx, bry, tpx, tpy, RGB::white);
}


void ShipRenderer::render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) {
    renderAt(gfx, position.X(), position.Y(), shape.Radius(), direction.Angle());
    if(position.X()+shape.Radius()>640)
    {
        renderAt(gfx, position.X()-640, position.Y(), shape.Radius(), direction.Angle());
    }

    if(position.X()-shape.Radius()<0)
    {
        renderAt(gfx, position.X()+640, position.Y(), shape.Radius(), direction.Angle());
    }

    if(position.Y()+shape.Radius()>480)
    {
        renderAt(gfx, position.X(), position.Y()-480, shape.Radius(), direction.Angle());
    }

    if(position.Y()-shape.Radius()<0)
    {
        renderAt(gfx, position.X(), position.Y()+480, shape.Radius(), direction.Angle());
    }
}