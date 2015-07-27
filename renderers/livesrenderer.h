#ifndef __LIVES_RENDERER_H__
#define __LIVES_RENDERER_H__

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include "renderers/renderer.h"

class LivesRenderer : public Renderer
{
public:
	LivesRenderer()
	{
	}

	~LivesRenderer()
	{
	}

    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) const override;

	void setLives(int liveCount)
	{
		this->liveCount = liveCount;
	}

	void setAlignment(TextAlignment alignment)
	{
		this->alignment = alignment;
	}

private:
	int liveCount;
	TextAlignment alignment;
};

#endif
