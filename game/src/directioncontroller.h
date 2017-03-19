#pragma once

#include <input/gamepad.h>
#include <direction.h>

class DirectionController
{

public:
	void control(GamepadSource &source, Direction &directionToControl);

	void releaseControl(GamepadSource &source);

	std::function<void()> upPressHandler;

	std::function<void()> upReleaseHandler;

	std::function<void()> leftPressHandler;

	std::function<void()> leftReleaseHandler;

	std::function<void()> rightPressHandler;

	std::function<void()> rightReleaseHandler;

};
