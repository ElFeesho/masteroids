#include "scorerenderer.h"

#include <sstream>

using std::stringstream;

void ScoreRenderer::render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour)
{
	stringstream sstream;
	sstream << "SCORE: " << score;
	gfx->drawText(position.X(), position.Y(), sstream.str(), colour, alignment);
}