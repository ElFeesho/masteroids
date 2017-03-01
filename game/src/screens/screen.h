#pragma once

class Gfx;
class Screen;

class ScreenListener
{
public:
    virtual void screenClosed(Screen &screen, int reason) = 0;
};

class Screen
{
public:
	virtual ~Screen() {}

    virtual void update(Gfx &gfx) = 0;

	virtual void screenShown() = 0;

	virtual void screenHidden() = 0;
};
