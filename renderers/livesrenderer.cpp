#include "livesrenderer.h"
#include <sstream>

using std::stringstream;

void LivesRenderer::render(GfxWrapper* gfx, Position& position, Shape& shape, Direction& direction){
    stringstream sstream;
    sstream << "LIVES: " << liveCount;
    gfx->drawText(position.X(), position.Y() + gfx->textHeight()+3, sstream.str(), colour, alignment);
}
