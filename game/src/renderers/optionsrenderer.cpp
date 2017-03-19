#include "optionsrenderer.h"
#include "../menu/options.h"
#include "../images/options_img.h"

#include <sstream>

using std::string;
using std::stringstream;

static const int LIVES = 0;
static const int DIFFICULTY = 1;
static const int TEAM_PLAY = 2;
static const int PLAYER_COUNT = 3;
static const int MAX_BULLETS = 4;
static const int MUSIC = 5;
static const int CONTROLS = 6;

static string difficultyLabels[] = {"Easy", "Medium", "Hard"};

void OptionsRenderer::setMenuSelection(int menuSelection)
{
	menu_sel = menuSelection;
}

void OptionsRenderer::render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const
{
	static long textHeight = (long) gfx.measureText("X").h;
	
    gfx.drawRect(120, 80, 403, 340, RGB::BLUE);
    gfx.drawImg(321 - options_width / 2, 81, options_width, options_height, options_img);

	int textPosition = 640 / 2;

	stringstream stringBuffer;;
	stringBuffer << "Lives: " << (Options::lives);
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 8), stringBuffer.str(), menu_sel == LIVES ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);

	stringBuffer.str("");
	stringBuffer << "Difficulty: " << difficultyLabels[Options::difficulty];
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 9), stringBuffer.str(), menu_sel == DIFFICULTY ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);

	stringBuffer.str("");
	stringBuffer << "Team Killing: " << (Options::team_kill == 0 ? "Off" : "On");
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 10), stringBuffer.str(), menu_sel == TEAM_PLAY ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);

	stringBuffer.str("");
	stringBuffer << "Players: " << Options::players;
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 11), stringBuffer.str(), menu_sel == PLAYER_COUNT ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);

	stringBuffer.str("");
	stringBuffer << "Max Bullets: " << Options::max_bullets;
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 12), stringBuffer.str(), menu_sel == MAX_BULLETS ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);

	stringBuffer.str("");
	stringBuffer << "Music: " << (Options::music ? "Yes" : "No");
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 13), stringBuffer.str(), menu_sel == MUSIC ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);

    gfx.drawText(false, textPosition, (int) (80 + textHeight * 14), "Configure Controls", menu_sel == CONTROLS ? RGB::YELLOW : RGB::WHITE, TextAlignment::CENTRE);
    gfx.drawText(false, textPosition, (int) (80 + textHeight * 16), "Start to Exit", RGB::WHITE, TextAlignment::CENTRE);
}
