#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "images/asteroid_banner.h"
#include "images/controllers.h"
#include "renderers/menurenderer.h"
#include "menuscreenitem.h"

class MenuListener
{
public:
	virtual ~MenuListener() {}

	virtual void menuStartGameSelected() = 0;

	virtual void menuOptionsSelected() = 0;

	virtual void menuAboutSelected() = 0;

	virtual void menuExitSelected() = 0;
};

class Menu : public MenuScreenItem
{
public:
	Menu(MenuListener *listener);

    void menuScreenPresented() override;
    void menuScreenHidden() override;

	bool update() override;

    void render(Gfx &gfx) override;

	Position &position() override;

	Shape &shape() override;

	Direction &direction() override;

	const AliveMonitor & aliveMonitor() override;

	const Renderer & renderer() override;

	void incrementMenu();

	void decrementMenu();

	void handleMenuSelection();

private:
    AlwaysAlive alwaysAliveMonitor;
	MenuListener *listener;
	MenuRenderer menuRenderer;
	unsigned int menu_sel { 0 };
	unsigned long next_change { 0 };
	char ldir { -1 };
};

#endif
