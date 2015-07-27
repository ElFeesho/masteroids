#ifndef __ASTEROIDRENDERER_H__
#define __ASTEROIDRENDERER_H__

#include <stdlib.h>
#include "../gfx/gfx.h"
#include "renderer.h"

class AsteroidRenderer : public Renderer
{
public:
    AsteroidRenderer();
    void renderAtLocation(Gfx &gfx, int x, int y, double rotation, double radius, RGB &colour) const;
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const override;

private:
	double peaks[6];
};

#endif
