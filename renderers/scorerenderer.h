#ifndef __SCORE_RENDERER_H__
#define __SCORE_RENDERER_H__

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include "renderers/renderer.h"

class ScoreRenderer : public Renderer
{
public:
	ScoreRenderer()
	{
	}

	~ScoreRenderer()
	{
	}

	void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) override;

	void setScore(int score)
	{
		this->score = score;
	}

	void setAlignment(TextAlignment alignment)
	{
		this->alignment = alignment;
	}

private:
	int score;
	TextAlignment alignment;
};

#endif
