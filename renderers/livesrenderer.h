#ifndef __LIVES_RENDERER_H__
#define __LIVES_RENDERER_H__

#include <gfx/gfx.h>
#include <position.h>
#include <shape.h>
#include "renderers/renderer.h"

class LivesRenderer : public Renderer
{
public:
    LivesRenderer() : colour(RGB::black) {}
    ~LivesRenderer() {}

    void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) override;

    void setLives(int liveCount) { this->liveCount = liveCount; }
    void setAlignment(TextAlignment alignment) { this->alignment = alignment; }
    void setColour(RGB &colour) { this->colour = colour; }
private:
    int liveCount;
    TextAlignment alignment;
    RGB colour;
};

#endif
