#include "gameoverscreen.h"
#include "input/gamepadinputmanager.h"

GameOverScreen::GameOverScreen(GameOverScreenListener &gameOverScreenListener) : listener(gameOverScreenListener), gameOverEntity(GameOver()), closeScreenHandler{[&]{
    listener.gameOverScreenShouldClose();
}}
{

}

GameOverScreen::~GameOverScreen()
{

}

void GameOverScreen::update(GfxWrapper &gfx)
{
	gameOverEntity.update();
	gameOverEntity.render(gfx);
}

void GameOverScreen::screenShown()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().addUpHandler(&closeScreenHandler);
}

void GameOverScreen::screenHidden()
{
    GamepadInputManager::sharedInstance().inputForPlayer(0).fire().removeUpHandler(&closeScreenHandler);
}
