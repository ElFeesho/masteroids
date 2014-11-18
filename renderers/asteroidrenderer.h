#ifndef __ASTEROIDRENDERER_H__
#define __ASTEROIDRENDERER_H__

#include <stdlib.h>
#include "../gfx/gfx.h"
#include "renderer.h"

class AsteroidRenderer : public Renderer {
public:
    AsteroidRenderer() {
        for (int i = 0; i < 6; i++) {
            peaks[i] = ((double) (rand() % 75) + 50) / 100.0f;
        }
    }

    void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction) {
        double sliceStep = ((2 * M_PI)/5.0);
        for (int i = 0; i < 6; i++) {
            if (i != 5) {
                double rot1 = (position.Rotation() + i * sliceStep);
                double rot2 = (position.Rotation() + (i + 1) * sliceStep);

                gfx->drawLine(position.X() + cos(rot1) * peaks[i] * shape.Radius(),
                        position.Y() + sin(rot1) * peaks[i] * shape.Radius(),
                        position.X() + cos(rot2) * peaks[i + 1] * shape.Radius(),
                        position.Y() + sin(rot2) * peaks[i + 1] * shape.Radius(), RGB::white);
            }
            else {
                double rot1 = (position.Rotation() + i * sliceStep);
                double rot2 = position.Rotation();
                gfx->drawLine(position.X() + cos(rot1) * peaks[i] * shape.Radius(),
                        position.Y() + sin(rot1) * peaks[i] * shape.Radius(),
                        position.X() + cos(rot2) * peaks[0] * shape.Radius(),
                        position.Y() + sin(rot2) * peaks[0] * shape.Radius(), RGB::white);
            }
        }
    }

private:
    double peaks[6];
};

#endif