#include "scorerenderer.h"

#include <sstream>

using std::stringstream;

void ScoreRenderer::render(Gfx &gfx, Position &position, Shape &, Direction &, RGB &colour) const
{
	stringstream sstream;
	sstream << "SCORE: " << score;
    gfx.drawText(false, position.X(), position.Y(), sstream.str(), colour, alignment);
}

void ScoreRenderer::setScore(int nscore)
{
	this->score = nscore;
}

void ScoreRenderer::setAlignment(TextAlignment nalignment)
{
	this->alignment = nalignment;
}