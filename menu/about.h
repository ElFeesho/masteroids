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
	virtual ~AboutListener() {}

	virtual void aboutClosed() = 0;
};

class About : public MenuScreenItem
{
public:
	About(AboutListener *listener);

	bool update() override
	{
		return aliveMonitor().alive();
	}

    void render(Gfx &gfx) override;

	Position &position() override
	{
		return Position::NONE;
	}

	Shape &shape() override
	{
		return Shape::NONE;
	}

	Direction &direction() override
	{
		return Direction::NONE;
	}

	AliveMonitor &aliveMonitor() override
	{
        return alivemonitor;
	}

	Renderer &renderer() override
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
