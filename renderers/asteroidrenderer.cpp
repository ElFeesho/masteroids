#include "renderers/asteroidrenderer.h"

AsteroidRenderer::AsteroidRenderer()
{
    for (int i = 0; i < 6; i++)
    {
        peaks[i] = ((double) (rand() % 75) + 50) / 100.0f;
    }
}

void AsteroidRenderer::renderAtLocation(GfxWrapper &gfx, int x, int y, double rotation, double radius) const
{
    double sliceStep = ((2 * M_PI) / 5.0);
    for (int i = 0; i < 6; i++)
    {
        if (i != 5)
        {
            double rot1 = (rotation + i * sliceStep);
            double rot2 = (rotation + (i + 1) * sliceStep);
            
            gfx.drawLine(x + cos(rot1) * peaks[i] * radius,
                         y + sin(rot1) * peaks[i] * radius,
                         x + cos(rot2) * peaks[i + 1] * radius,
                    y + sin(rot2) * peaks[i + 1] * radius, RGB::white);
        }
        else
        {
            double rot1 = (rotation + i * sliceStep);
            double rot2 = rotation;
            gfx.drawLine(x + cos(rot1) * peaks[i] * radius,
                         y + sin(rot1) * peaks[i] * radius,
                         x + cos(rot2) * peaks[0] * radius,
                         y + sin(rot2) * peaks[0] * radius, RGB::white);
        }
    }
}

void AsteroidRenderer::render(GfxWrapper &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour) const
{
    if (position.X() + shape.Radius() > 640)
    {
        renderAtLocation(gfx, position.X() - 640, position.Y(), position.Rotation(), shape.Radius());
    }
    
    if (position.X() - shape.Radius() < 0)
    {
        renderAtLocation(gfx, 640 + position.X(), position.Y(), position.Rotation(), shape.Radius());
    }
    
    if (position.Y() + shape.Radius() > 480)
    {
        renderAtLocation(gfx, position.X(), position.Y() - 480, position.Rotation(), shape.Radius());
    }
    
    if (position.Y() - shape.Radius() < 0)
    {
        renderAtLocation(gfx, position.X(), position.Y() + 480, position.Rotation(), shape.Radius());
    }
    
    
    renderAtLocation(gfx, position.X(), position.Y(), position.Rotation(), shape.Radius());
}

