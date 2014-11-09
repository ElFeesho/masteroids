#include "gameover.h"

#include <ogcsys.h>
#include <gccore.h>
#include <string.h>
#include <cstdio>

#include "ship.h"
#include "options.h"

#include "GRRLIB.h"
#include "game_over_img.h"
#include "font5.h"

#include "gamepadinputmanager.h"
#include "engine.h"

using std::sprintf;

GameOver::GameOver() : colour(RGB(1.0f, 1.0f, 1.0f)), colourHighlight(RGB(1.0f, 0.8f, 0.0f))
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

GameOver::~GameOver()
{
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

bool GameOver::update()
{
	return true;
}

void GameOver::buttonDown(GamepadButton button)
{

}

void GameOver::buttonUp(GamepadButton button)
{
	if(button == BUTTON_FIRE)
	{
		get_engine()->set_mode(0);
	}
}
void GameOver::render(GfxWrapper* gfx)
{
	if(Options::players == 1) /* 1 player */
	{
		gfx->drawImg((640-game_over_width)/2,(480-game_over_height)/2, game_over_width, game_over_height, game_over_img);
		char score[64] = { 0 };
		sprintf(score, "Your Score Was: %d",Ship::scores[0]);
		gfx->drawText((640-strlen(score)*font5_char_width)/2, (480-game_over_height)/2+100, score, colour);
	}
	else
	{
		gfx->drawImg((640-game_over_width)/2,(350-game_over_height)/2, game_over_width, game_over_height, game_over_img);
		char score[64] = { 0 };
		int highest = -1;

		for(int i = 0;i<Options::players;i++)
		{
			if(Ship::scores[i]>highest)
				highest = Ship::scores[i];
		}
		for(int i = 0;i<Options::players;i++)
		{
			memset(score,0,64);
			sprintf(score, "Player %d Score: %d",i+1,Ship::scores[i]);
			if(Ship::scores[i]==highest)
			{
				gfx->drawText((640-strlen(score)*font5_char_width)/2, (480-game_over_height)/2+50+(font5_char_high*i+20), score, colourHighlight);
			}
			else
			{
				gfx->drawText((640-strlen(score)*font5_char_width)/2, (480-game_over_height)/2+50+(font5_char_high*i+10), score,  colour);
			}
		}
	}
	gfx->drawText((640-(23*font5_char_width))/2, 380, "Push 2 Or A To Continue", colour);
}
