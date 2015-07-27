#include "scorerenderer.h"

#include <sstream>

using std::stringstream;

void ScoreRenderer::render(Gfx &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour) const
{
	stringstream sstream;
	sstream << "SCORE: " << score;
    gfx.drawText(false, position.X(), position.Y(), sstream.str(), colour, alignment);
}
