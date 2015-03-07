#ifndef __GAMEOVERSCREEN_H__
#define __GAMEOVERSCREEN_H__

#include "screen.h"
#include "gameover.h"

class GameOverScreen : public Screen
{
public:
	GameOverScreen();

	~GameOverScreen();

	void setListener(ScreenListener *listener) override;

	void update(GfxWrapper *gfx) override;

	void screenShown() override;

	void screenHidden() override;

private:
	ScreenListener *listener;
	GameOver gameOverEntity;
};

#endif

