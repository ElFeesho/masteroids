#include "gameoverscreen.h"

GameOverScreen::GameOverScreen() : gameOverEntity(GameOver()) {
}

GameOverScreen::~GameOverScreen() {

}

void GameOverScreen::setListener(ScreenListener* listener){
    this->listener = listener;
}

void GameOverScreen::update(GfxWrapper *gfx) {
    gameOverEntity.update();
    gameOverEntity.render(gfx);
}

void GameOverScreen::screenShown() {

}

void GameOverScreen::screenHidden() {

}