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

#include "engine.h"

#include "controlconf.h"

using std::sprintf;

GameOver::GameOver()
{
}

GameOver::~GameOver()
{

}

bool GameOver::update()
{
	if(Options::players == 1) /* 1 player */
	{
		GRRLIB_DrawImg((640-game_over_width)/2,(480-game_over_height)/2, game_over_width, game_over_height, game_over_img, 0.0, 1.0);
		char score[64] = { 0 };
		sprintf(score, "Your Score Was: %d",Ship::scores[0]);
		GRRLIB_Print((640-strlen(score)*font5_char_width)/2, (480-game_over_height)/2+100, font5_char_width, font5_char_high, score,font5, 0xffff, 0x0000);
	}
	else
	{
		GRRLIB_DrawImg((640-game_over_width)/2,(350-game_over_height)/2, game_over_width, game_over_height, game_over_img, 0.0, 1.0);
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
				GRRLIB_Print((640-strlen(score)*font5_char_width)/2, (480-game_over_height)/2+50+(font5_char_high*i+20), font5_char_width, font5_char_high, score,font5, 0xffa0, 0x0000);
			}
			else
			{
				GRRLIB_Print((640-strlen(score)*font5_char_width)/2, (480-game_over_height)/2+50+(font5_char_high*i+10), font5_char_width, font5_char_high, score, font5, 0xffff, 0x0000);
			}
		}
	}
	GRRLIB_Print((640-(23*font5_char_width))/2, 380, font5_char_width, font5_char_high, (char*)"Push 2 Or A To Continue",font5, 0xffff, 0x0000);

	for(int i = 0;i<Options::players;i++)
		if(ControlConf::button_down(i,BUTTON_SHOOT))
		{
			get_engine()->set_mode(0);
			return false;
		}
	return true;
}
