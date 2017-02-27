#pragma once

#include "input/gamepad.h"
#include "direction.h"

class DirectionController
{
private:

public:
	DirectionController(GamepadSource &source) : gamepadSource(source), directionToControl(Direction::NONE)
	{
		attachListeners();
	}

	DirectionController(GamepadSource &source, DirectionController &copy)
			: gamepadSource(source), directionToControl(copy.directionToControl)
	{
		attachListeners();
	}


	DirectionController(GamepadSource &source, Direction &directon) : gamepadSource(source), directionToControl(directon)
	{
		attachListeners();
	}

	~DirectionController()
	{
		gamepadSource.up().removeDownHandler();
		gamepadSource.up().removeUpHandler();
		gamepadSource.left().removeDownHandler();
		gamepadSource.left().removeUpHandler();
		gamepadSource.right().removeDownHandler();
		gamepadSource.right().removeUpHandler();
	}

	void attachListeners()
	{
		gamepadSource.up().addDownHandler(upPressHandler);
		gamepadSource.up().addUpHandler(upReleaseHandler);
		gamepadSource.left().addDownHandler(leftPressHandler);
		gamepadSource.left().addUpHandler(leftReleaseHandler);
		gamepadSource.right().addDownHandler(rightPressHandler);
		gamepadSource.right().addUpHandler(rightReleaseHandler);
	}

private:
	GamepadSource &gamepadSource;
    Direction &directionToControl;

	ButtonCommandLambda upPressHandler;

	ButtonCommandLambda upReleaseHandler{std::unique_ptr<std::function<void()>>([&]()
	{
		directionToControl.Speed(0.0f);
	})};


	ButtonCommandLambda leftPressHandler{std::unique_ptr<std::function<void()>>([&]()
	{
		directionToControl.Spin(-0.1f);
	})};

	ButtonCommandLambda leftReleaseHandler{std::unique_ptr<std::function<void()>>([&]()
	{
		directionToControl.Spin(0.0f);
	})};

	ButtonCommandLambda rightPressHandler{std::unique_ptr<std::function<void()>>([&]()
	{
		directionToControl.Spin(0.1f);
	})};

	ButtonCommandLambda rightReleaseHandler{std::unique_ptr<std::function<void()>>([&]()
	{
		directionToControl.Spin(0.0f);
	})};
};
