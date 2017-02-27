#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "menu.h"

#include "input/gamepadinputmanager.h"
#include "gametime.h"

static std::function<void()> firePressHandler;

static std::function<void()> upPressHandler;
static std::function<void()> downPressHandler;
static std::function<void()> upReleaseHandler;
static std::function<void()> downReleaseHandler;

Menu::Menu(MenuListener *nlistener)
        : listener(nlistener), menuRenderer(MenuRenderer()), menu_sel(0), next_change(0), ldir(-1) {
    std::cout << "Menu" << std::endl;
    firePressHandler = [&]() {
        next_change = 0;
        ldir = -1;
        handleMenuSelection();
    };

    upPressHandler = [&]() {
        ldir = 0;
        decrementMenu();
        next_change = GameTime::getMillis() + 500;
    };

    downPressHandler = [&]() {
        ldir = 1;
        incrementMenu();

        next_change = GameTime::getMillis() + 500;
    };

    upReleaseHandler = [&]() {
        next_change = 0;
        ldir = -1;
    };

    downReleaseHandler = [&]() {
        next_change = 0;
        ldir = -1;
    };

}

Menu::~Menu() {
    //GamepadInputManager::sharedInstance()->inputForPlayer(0)->removeListener(this);
    std::cout << "~Menu" << std::endl;
}

void Menu::menuScreenPresented() {
    GamepadSource &source = GamepadInputManager::sharedInstance().inputForPlayer(0);
    source.fire().addUpHandler(firePressHandler);
    source.up().addDownHandler(upPressHandler);
    source.up().addUpHandler(upReleaseHandler);
    source.down().addDownHandler(downPressHandler);
    source.down().addUpHandler(downReleaseHandler);
}

void Menu::menuScreenHidden() {
    GamepadSource &source = GamepadInputManager::sharedInstance().inputForPlayer(0);
    source.fire().removeUpHandler();
    source.up().removeDownHandler();
    source.up().removeUpHandler();
    source.down().removeDownHandler();
    source.down().removeUpHandler();
}

bool Menu::update() {
    unsigned long cticks = GameTime::getMillis();

    if (cticks > next_change && next_change != 0) {
        next_change = cticks + 200;
        if (ldir == 1) {
            if (menu_sel < 3) {
                menu_sel++;
            }
            else {
                menu_sel = 0;
            }
        }
        else if (ldir == 0) {
            if (menu_sel > 0) {
                menu_sel--;
            }
            else {
                menu_sel = 3;
            }
        }
    }

    menuRenderer.setMenuItemSelection(menu_sel);
    return true;
}

void Menu::render(Gfx &gfx) {
    renderer().render(gfx, position(), shape(), direction());
}

void Menu::incrementMenu() {
    if (menu_sel < 3) {
        menu_sel++;
    }
    else {
        menu_sel = 0;
    }
}

void Menu::decrementMenu() {
    if (menu_sel > 0) {
        menu_sel--;
    }
    else {
        menu_sel = 3;
    }
}

void Menu::handleMenuSelection() {
    switch (menu_sel) {
        case 0:
            listener->menuStartGameSelected();
            break;
        case 1:
            listener->menuOptionsSelected();
            break;
        case 2:
            listener->menuAboutSelected();
            break;
        case 3:
            listener->menuExitSelected();
            break;
    }
}

Position &Menu::position() {
    return Position::NONE;
}

Shape &Menu::shape() {
    return Shape::NONE;
}

Direction &Menu::direction() {
    return Direction::NONE;
}

const AliveMonitor &Menu::aliveMonitor() {
    return alwaysAliveMonitor;
}

const Renderer &Menu::renderer() {
    return menuRenderer;
}