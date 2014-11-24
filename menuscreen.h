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

class MenuScreen
        : public Screen, public AboutListener, public ControlConfListener, public MenuListener, public OptionsListener {
public:
    MenuScreen();

    ~MenuScreen();

    void update(GfxWrapper *gfx);

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
    AsteroidFactory asteroidFactory;
    Entity *activeMenu;

    EntityList entityList;
    ScreenListener *listener;
};

#endif