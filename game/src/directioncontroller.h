#pragma once

#include <input/gamepad.h>
#include <direction.h>

class DirectionController
{

public:
	void control(GamepadSource &source, Direction &directionToControl)
	{
		upPressHandler = {[&]()
		{
			directionToControl.Speed(0.1f);
		}};

		upReleaseHandler = {[&]()
		{
			directionToControl.Speed(0.0f);
		}};

		leftPressHandler = {[&]()
		{
			directionToControl.Spin(-0.1f);
		}};

		leftReleaseHandler = {[&]()
		{
			directionToControl.Spin(0.0f);
		}};

		rightPressHandler = {[&]()
		{
			directionToControl.Spin(0.1f);
		}};

		rightReleaseHandler = {[&]()
		{
			directionToControl.Spin(0.0f);
		}};

		source.up().addDownHandler(&upPressHandler);
		source.up().addUpHandler(&upReleaseHandler);
		source.left().addDownHandler(&leftPressHandler);
		source.left().addUpHandler(&leftReleaseHandler);
		source.right().addDownHandler(&rightPressHandler);
		source.right().addUpHandler(&rightReleaseHandler);
	}

	void releaseControl(GamepadSource &source)
	{
		source.up().removeAllHandlers();
		source.left().removeAllHandlers();
		source.right().removeAllHandlers();
	}

	std::function<void()> upPressHandler;

	std::function<void()> upReleaseHandler;

	std::function<void()> leftPressHandler;

	std::function<void()> leftReleaseHandler;

	std::function<void()> rightPressHandler;

	std::function<void()> rightReleaseHandler;

};
