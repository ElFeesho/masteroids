#include "livesrenderer.h"
#include <sstream>

using std::stringstream;

void LivesRenderer::render(Gfx &gfx, Position &position, Shape &, Direction &, RGB &colour) const
{
	stringstream sstream;
	sstream << "LIVES: " << liveCount;
    gfx.drawText(false, position.X(), position.Y() + gfx.measureText(sstream.str()).h + 3, sstream.str(), colour, alignment);
}
