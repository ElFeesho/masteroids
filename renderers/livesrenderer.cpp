#include "livesrenderer.h"

void LivesRenderer::render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction){
    gfx->drawText(position.X(), position.Y() + gfx->textHeight()+3, "LIVES", RGB::white, LEFT);
    Position shipPosition = Position(position.X()+shipShape.Radius(), position.Y()+gfx->textHeight()*3, 0);
    Direction dir = Direction(0,-M_PI_2);
    for(int i = 0; i < liveCount; i++) {
        shipRenderer.render(gfx, shipPosition, shipShape, dir);
        shipPosition.translate(shipShape.Radius()*2, 0);
    }
}
