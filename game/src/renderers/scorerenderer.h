#pragma once

#include "gfx/gfx.h"
#include "position.h"
#include "shape.h"
#include <renderer.h>

class ScoreRenderer : public Renderer
{
public:
    void render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::WHITE) const override;

	void setScore(int nscore);
	void setAlignment(TextAlignment nalignment);
	
private:
	int score;
	TextAlignment alignment;
};
