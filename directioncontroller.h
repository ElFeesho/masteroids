#ifndef __DIRECTIONCONTROLLER_H__
#define __DIRECTIONCONTROLLER_H__

#include "input/gamepad.h"
#include "direction.h"

class DirectionController
{

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
		gamepadSource.up().removeDownHandler(&upPressHandler);
		gamepadSource.up().removeUpHandler(&upReleaseHandler);
		gamepadSource.left().removeDownHandler(&leftPressHandler);
		gamepadSource.left().removeUpHandler(&leftReleaseHandler);
		gamepadSource.right().removeDownHandler(&rightPressHandler);
		gamepadSource.right().removeUpHandler(&rightReleaseHandler);
	}

	void attachListeners()
	{
		gamepadSource.up().addDownHandler(&upPressHandler);
		gamepadSource.up().addUpHandler(&upReleaseHandler);
		gamepadSource.left().addDownHandler(&leftPressHandler);
		gamepadSource.left().addUpHandler(&leftReleaseHandler);
		gamepadSource.right().addDownHandler(&rightPressHandler);
		gamepadSource.right().addUpHandler(&rightReleaseHandler);
	}

private:
	Direction &directionToControl;
	GamepadSource &gamepadSource;

	std::function<void()> upPressHandler{[&]()
	{
		directionToControl.Speed(0.1f);
	}};

	std::function<void()> upReleaseHandler{[&]()
	{
		directionToControl.Speed(0.0f);
	}};


	std::function<void()> leftPressHandler{[&]()
	{
		directionToControl.Spin(-0.1f);
	}};

	std::function<void()> leftReleaseHandler{[&]()
	{
		directionToControl.Spin(0.0f);
	}};

	std::function<void()> rightPressHandler{[&]()
	{
		directionToControl.Spin(0.1f);
	}};

	std::function<void()> rightReleaseHandler{[&]()
	{
		directionToControl.Spin(0.0f);
	}};
};

#endif
