#ifndef __GAMEOVERRENDERER_H__
#define __GAMEOVERRENDERER_H__

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include "renderer.h"

class GameOverRenderer : public Renderer
{

public:
	virtual ~GameOverRenderer();

    void render(GfxWrapper &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) const override;
};

#endif
