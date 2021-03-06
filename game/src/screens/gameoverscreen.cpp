#include "gameoverscreen.h"
#include "input/gamepadinputmanager.h"

GameOverScreen::GameOverScreen(GameOverScreenListener &gameOverScreenListener) : listener(gameOverScreenListener), gameOverEntity(), closeScreenHandler{[&]{
    listener.gameOverScreenShouldClose();
}}
{

}

void GameOverScreen::update(Gfx &gfx)
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
