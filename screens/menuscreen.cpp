#include "menuscreen.h"

MenuScreen::MenuScreen(MenuScreenListener &menuScreenListener) : menuListener(menuScreenListener), menuScreen(this),
                                                                 optionsScreen(this), aboutScreen(this) {
    for (int i = 0; i < 16; i++) {
        entityList.add(asteroidFactory.createAsteroid(75.0f));
    }
}

void MenuScreen::screenShown() {
    activeMenu = &menuScreen;
    activeMenu->menuScreenPresented();
}

void MenuScreen::screenHidden() {
    activeMenu->menuScreenHidden();
}

void MenuScreen::aboutClosed() {
    activateScreen(&menuScreen);
}

void MenuScreen::menuStartGameSelected() {
    menuListener.menuScreenShouldShowGameScreen();
}

void MenuScreen::menuOptionsSelected() {
    activateScreen(&optionsScreen);
}

void MenuScreen::menuAboutSelected() {
    activateScreen(&aboutScreen);
}

void MenuScreen::menuExitSelected() {
    menuListener.menuScreenShouldExitGame();
}

void MenuScreen::optionsControllerConfigSelected() {
}

void MenuScreen::optionsMenuClosed() {
    activateScreen(&menuScreen);
}

void MenuScreen::update(Gfx &gfx) {
    entityList.updateAll();
    activeMenu->update();
    entityList.renderAll(gfx);
    activeMenu->render(gfx);
}

void MenuScreen::activateScreen(MenuScreenItem *screenItem) {
    activeMenu->menuScreenHidden();
    activeMenu = screenItem;
    activeMenu->menuScreenPresented();
}
