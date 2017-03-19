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

	bool update() override;

    void render(Gfx &gfx) override;

	Position &position() override;

	Shape &shape() override;

	Direction &direction() override;

	const AliveMonitor & aliveMonitor() override;

	const Renderer & renderer() override;

    void menuScreenPresented() override;

    void menuScreenHidden() override;

private:
    AlwaysAlive alivemonitor;
	AboutRenderer aboutRenderer;
};

#endif
