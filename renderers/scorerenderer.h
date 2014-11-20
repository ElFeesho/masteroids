#ifndef __SCORE_RENDERER_H__
#define __SCORE_RENDERER_H__

#include <gfx/gfx.h>
#include <position.h>
#include <shape.h>
#include "renderers/renderer.h"

class ScoreRenderer : public Renderer
{
public:
    ScoreRenderer() : colour(RGB::black) {}
    ~ScoreRenderer() {}

    void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) override;

    void setScore(int score) { this->score = score; }
    void setAlignment(TextAlignment alignment) { this->alignment = alignment; }
    void setColour(RGB &colour) { this->colour = colour; }
private:
    int score;
    TextAlignment alignment;
    RGB colour;
};

#endif
