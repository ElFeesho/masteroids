#include "gameover.h"
#include "input/gamepadinputmanager.h"

GameOver::GameOver() : gameOverRenderer(GameOverRenderer()) {
    GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

GameOver::~GameOver() {
    GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

bool GameOver::update() {
    return aliveMonitor().alive();
}

bool GameOver::buttonDown(GamepadButton button) {
    return false;
}

bool GameOver::buttonUp(GamepadButton button) {
    if (button == BUTTON_FIRE) {
    }
    return false;
}

void GameOver::render(GfxWrapper *gfx) {
    renderer().render(gfx, position(), shape(), direction());
}

Position &GameOver::position() {
    return Position::NONE;
}

Shape &GameOver::shape() {
    return Shape::NONE;
}

Direction &GameOver::direction() {
    return Direction::NONE;
}

AliveMonitor &GameOver::aliveMonitor() {
    return AlwaysAlive::alivemonitor;
}

Renderer &GameOver::renderer() {
    return gameOverRenderer;
}
