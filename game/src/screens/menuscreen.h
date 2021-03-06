#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include "entity.h"
#include "screen.h"
#include "menu/menu.h"
#include "menu/options.h"
#include "menu/about.h"
#include "menu/controlconf.h"
#include "menu/menuscreenitem.h"
#include "entitylist.h"
#include "asteroidfactory.h"

class MenuScreenListener
{
public:
    virtual ~MenuScreenListener() {}

    virtual void menuScreenShouldShowGameScreen() = 0;
    virtual void menuScreenShouldExitGame() = 0;
};

class MenuScreen : public Screen, public AboutListener, public ControlConfListener, public MenuListener, public OptionsListener
{
public:
    MenuScreen(MenuScreenListener &menuScreenListener);

    void update(Gfx &gfx);

	void setListener(ScreenListener *listener);

	void aboutClosed();

	void controlConfClosed();

	void menuStartGameSelected();

	void menuOptionsSelected();

	void menuAboutSelected();
    void menuExitSelected();

	void optionsControllerConfigSelected();

	void optionsMenuClosed();

	void screenShown();

	void screenHidden();

private:
    AsteroidFactory asteroidFactory;

    void activateScreen(MenuScreenItem *screenItem);

    MenuScreenListener &menuListener;
    MenuScreenItem *activeMenu;

    EntityList entityList;

	ScreenListener *listener;
    Menu menuScreen;
    Options optionsScreen;
    ControlConf controllerConfigScreen;
    About aboutScreen;
};

#endif
