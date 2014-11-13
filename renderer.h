#ifndef RENDERER_H
#define RENDERER_H

#include "position.h"

class GfxWrapper;

class Renderer
{
public:
	virtual ~Renderer() {}
	virtual void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) = 0;
};

#endif // RENDERER_H
