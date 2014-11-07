#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include "entity.h"
#include "screen.h"
#include "menu.h"
#include "entitylist.h"

class MenuScreen : public Screen, public MenuListener
{
public:
	MenuScreen();
	~MenuScreen();

	void update(GfxWrapper *gfx);
	void setListener(ScreenListener *listener);


	void menuStartGameSelected();
	void menuOptionsSelected();
	void menuAboutSelected();

private:
	Menu *menu;
	EntityList entityList;
	ScreenListener *listener;
};

#endif