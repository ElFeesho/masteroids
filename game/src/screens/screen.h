#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <vector>
#include "gfx/gfx.h"
#include "entity.h"

using std::vector;

class Screen;

class ScreenListener
{
public:
    virtual void screenClosed(Screen &screen, int reason) = 0;
};

class Screen
{
public:
	virtual ~Screen()
	{
    }

    virtual void update(Gfx &gfx) = 0;

	virtual void screenShown() = 0;

	virtual void screenHidden() = 0;
};

#endif
