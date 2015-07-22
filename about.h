#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "renderers/aboutrenderer.h"
#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "menuscreenitem.h"

class AboutListener
{
public:
	virtual ~AboutListener()
	{
	}

	virtual void aboutClosed() = 0;
};

class About : public MenuScreenItem
{
public:
	About(AboutListener *listener);

	~About();

	bool update()
	{
		return aliveMonitor().alive();
	}

    void render(GfxWrapper &gfx);

	Position &position()
	{
		return Position::NONE;
	}

	Shape &shape()
	{
		return Shape::NONE;
	}

	Direction &direction()
	{
		return Direction::NONE;
	}

	AliveMonitor &aliveMonitor()
	{
        return alivemonitor;
	}

	Renderer &renderer()
	{
		return aboutRenderer;
	}

    void menuScreenPresented() override;

    void menuScreenHidden() override;

private:
    AlwaysAlive alivemonitor;
	AboutListener *listener;
	AboutRenderer aboutRenderer;
};

#endif
