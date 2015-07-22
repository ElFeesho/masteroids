#ifndef __ASTEROIDRENDERER_H__
#define __ASTEROIDRENDERER_H__

#include <stdlib.h>
#include "../gfx/gfx.h"
#include "renderer.h"

class AsteroidRenderer : public Renderer
{
public:
    AsteroidRenderer();
    void renderAtLocation(GfxWrapper &gfx, int x, int y, double rotation, double radius) const;
    void render(GfxWrapper &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) const override;

private:
	double peaks[6];
};

#endif
