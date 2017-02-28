#ifndef __SCORE_RENDERER_H__
#define __SCORE_RENDERER_H__

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include <renderer.h>

class ScoreRenderer : public Renderer
{
public:
	ScoreRenderer()
	{
	}

	~ScoreRenderer()
	{
	}

    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const override;

	void setScore(int nscore)
	{
		this->score = nscore;
	}

	void setAlignment(TextAlignment nalignment)
	{
		this->alignment = nalignment;
	}

private:
	int score;
	TextAlignment alignment;
};

#endif
