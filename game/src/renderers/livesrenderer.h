#ifndef __LIVES_RENDERER_H__
#define __LIVES_RENDERER_H__

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include <renderer.h>

class LivesRenderer : public Renderer
{
public:
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const override;

	void setLives(int nliveCount)
	{
		this->liveCount = nliveCount;
	}

	void setAlignment(TextAlignment nalignment)
	{
		this->alignment = nalignment;
	}

private:
	int liveCount;
	TextAlignment alignment;
};

#endif
