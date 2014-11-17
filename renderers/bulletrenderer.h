#ifndef __BULLET_RENDERER_H__
#define __BULLET_RENDERER_H__

#include "../gfx/gfx.h"
#include "renderer.h"

class BulletRenderer : public Renderer {
public:
    BulletRenderer() {
    }

    ~BulletRenderer() {
    }

    void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) {
        gfx->drawRect(position.X() - shape.Radius(),
                position.Y() - shape.Radius(),
                shape.Radius() * 2,
                shape.Radius() * 2,
                RGB::white);
    }
};


#endif