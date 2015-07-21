#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include "entity.h"
#include "screen.h"
#include "menu.h"
#include "options.h"
#include "about.h"
#include "entitylist.h"
#include "controlconf.h"
#include "asteroidfactory.h"
#include "menuscreenitem.h"

class MenuScreenListener
{
public:
    virtual ~MenuScreenListener() {}

    virtual void menuScreenShouldShowGameScreen() = 0;
    virtual void menuScreenShouldExitGame() = 0;
};

class MenuScreen
		: public Screen, public AboutListener, public ControlConfListener, public MenuListener, public OptionsListener
{
public:
    MenuScreen(MenuScreenListener &menuScreenListener);

	~MenuScreen();

    void update(GfxWrapper &gfx);

	void setListener(ScreenListener *listener);

	void aboutClosed();

	void controlConfClosed();

	void menuStartGameSelected();

	void menuOptionsSelected();

	void menuAboutSelected();

	void optionsControllerConfigSelected();

	void optionsMenuClosed();

	void screenShown();

	void screenHidden();

private:

    void activateScreen(MenuScreenItem *screenItem);

    MenuScreenListener &menuListener;
	AsteroidFactory asteroidFactory;
    MenuScreenItem *activeMenu;

	EntityList entityList;
	ScreenListener *listener;
    About aboutScreen;
    ControlConf controllerConfigScreen;
    Options optionsScreen;
    Menu menuScreen;
};

#endif
