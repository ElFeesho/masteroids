#include "menuscreen.h"

#include "asteroidfactory.h"

MenuScreen::MenuScreen() {

}

MenuScreen::~MenuScreen() {

}

void MenuScreen::screenShown() {
    for (int i = 0; i < 32; i++) {
        entityList.add(AsteroidFactory::createAsteroid(25.0f));
    }

    activeMenu = new Menu(this);
}

void MenuScreen::screenHidden() {
    entityList.clear();
    delete activeMenu;
}

void MenuScreen::aboutClosed() {
    delete activeMenu;
    activeMenu = new Menu(this);
}

void MenuScreen::controlConfClosed() {
    delete activeMenu;
    activeMenu = new Options(this);
}

void MenuScreen::menuStartGameSelected() {
    listener->screenClosed(this, 1);
}

void MenuScreen::menuOptionsSelected() {
    delete activeMenu;
    activeMenu = new Options(this);
}

void MenuScreen::menuAboutSelected() {
    delete activeMenu;
    activeMenu = new About(this);
}

void MenuScreen::optionsControllerConfigSelected() {
    delete activeMenu;
    activeMenu = new ControlConf(this);
}

void MenuScreen::optionsMenuClosed() {
    delete activeMenu;
    activeMenu = new Menu(this);
}


void MenuScreen::update(GfxWrapper *gfx) {
    entityList.updateAll();
    activeMenu->update();
    entityList.renderAll(gfx);
    activeMenu->render(gfx);
}

void MenuScreen::setListener(ScreenListener *listener) {
    this->listener = listener;
}
