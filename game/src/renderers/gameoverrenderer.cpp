#include "gameoverrenderer.h"
#include "menu/options.h"
#include "images/game_over_img.h"

void GameOverRenderer::render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const
{
    static float textHeight = gfx.measureText("W").h;
	
	if (Options::players == 1) /* 1 player */
	{
        gfx.drawImg((640 - game_over_width) / 2, (480 - game_over_height) / 2, game_over_width, game_over_height, game_over_img);
		char score[64] = {0};
		//sprintf(score, "Your Score Was: %d",Ship::scores[0]);
        gfx.drawText(false, 320, (480 - game_over_height) / 2 + 100, score, RGB::WHITE, TextAlignment::CENTRE);
	}
	else
	{
        gfx.drawImg((640 - game_over_width) / 2, (350 - game_over_height) / 2, game_over_width, game_over_height, game_over_img);
		char score[64] = {0};

		for (int i = 0; i < Options::players; i++)
		{
			//if(Ship::scores[i]>highest)
			//highest = Ship::scores[i];
		}
		for (int i = 0; i < Options::players; i++)
		{
			memset(score, 0, 64);
			//sprintf(score, "Player %d Score: %d",i+1,Ship::scores[i]);
			//if(Ship::scores[i]==highest)
			{
                gfx.drawText(false, 320, (480 - game_over_height) / 2 + 50 + (textHeight * i + 20), score, RGB::YELLOW, TextAlignment::CENTRE);
			}
			//else
			{
                gfx.drawText(false, 320, (480 - game_over_height) / 2 + 50 + (textHeight * i + 10), score, RGB::WHITE, TextAlignment::CENTRE);
			}
		}
	}
    gfx.drawText(false, 320, 380, "Push 2 Or A To Continue", RGB::WHITE, TextAlignment::CENTRE);
}
