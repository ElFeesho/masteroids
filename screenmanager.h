#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include "screen.h"

class GfxWrapper;

class ScreenManager : public ScreenListener
{
public:
	ScreenManager();

	~ScreenManager();

	void screenClosed(Screen *screen, int reason);

	void update(GfxWrapper *gfx);

private:
	Screen *activeScreen;
	Screen *menuScreen;
	Screen *gameScreen;
	Screen *gameOverScreen;

	void switchScreen(Screen *newScreen);
};

#endif