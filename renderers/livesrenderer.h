#ifndef __LIVES_RENDERER_H__
#define __LIVES_RENDERER_H__

#include <gfx/gfx.h>
#include <position.h>
#include <shape.h>
#include "renderers/renderer.h"
#include "renderers/shiprenderer.h"

class LivesRenderer : public Renderer
{
public:
    LivesRenderer() : shipRenderer(ShipRenderer()), shipShape(Shape(5.0f)) {};
    ~LivesRenderer() {};

    void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) override;

    void setLives(int liveCount) { this->liveCount = liveCount; }
private:
    int liveCount;
    ShipRenderer shipRenderer;
    Shape shipShape;
};

#endif
