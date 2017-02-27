#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include "entity.h"
#include "screen.h"
#include "menu.h"
#include "options.h"
#include "about.h"
#include "entitylist.h"
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
		: public Screen, public AboutListener, public MenuListener, public OptionsListener
{
public:
    MenuScreen(MenuScreenListener &menuScreenListener);

    void update(Gfx &gfx) override;

	void aboutClosed() override;

	void menuStartGameSelected() override;

	void menuOptionsSelected() override;

	void menuAboutSelected() override;
    void menuExitSelected() override;

	void optionsControllerConfigSelected() override;

	void optionsMenuClosed() override;

	void screenShown() override;

	void screenHidden() override;

private:
    AsteroidFactory asteroidFactory;

    void activateScreen(MenuScreenItem *screenItem);

    MenuScreenListener &menuListener;
    MenuScreenItem *activeMenu;

    EntityList entityList;

    Menu menuScreen;
    Options optionsScreen;
    About aboutScreen;

};

#endif
