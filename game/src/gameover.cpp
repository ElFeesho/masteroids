#include "gameover.h"
#include "input/gamepadinputmanager.h"

GameOver::GameOver() : gameOverRenderer(GameOverRenderer()) {}

bool GameOver::update()
{
	return aliveMonitor().alive();
}

void GameOver::render(Gfx &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

Position &GameOver::position()
{
	return Position::NONE;
}

Shape &GameOver::shape()
{
	return Shape::NONE;
}

Direction &GameOver::direction()
{
	return Direction::NONE;
}

AliveMonitor &GameOver::aliveMonitor()
{
    return alwaysAliveMonitor;
}

Renderer &GameOver::renderer()
{
	return gameOverRenderer;
}
