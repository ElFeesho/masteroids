#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"
#include "gfx/gfx.h"
#include "input/gamepad.h"
#include "renderers/pausedialogrenderer.h"

class PauseDialogListener
{
public:
	virtual ~PauseDialogListener()
	{
	}

	virtual void ingameContinueSelected() = 0;

	virtual void ingameQuitSelected() = 0;
};

class PauseDialog : public Entity
{
public:
	PauseDialog(GamepadSource &gamepad, PauseDialogListener *listener);

	~PauseDialog();

    void shown();

	bool update() override;

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

	const AliveMonitor &aliveMonitor() override
	{
        return alwaysAliveMonitor;
	}

	const Renderer &renderer() override
	{
		return pauseDialogRenderer;
	}

	void reset();

private:
    AlwaysAlive alwaysAliveMonitor;
	GamepadSource &gamepad;
	PauseDialogListener *listener;
	PauseDialogRenderer pauseDialogRenderer;
	int menu_sel;
	void highlightMenu(int menuSelection);

	std::function<void()> leftHandler{
			[&]()
			{
				highlightMenu(0);
			}
	};


	std::function<void()> rightHandler{
			[&]()
			{
				highlightMenu(1);
			}
	};

	std::function<void()> fireHandler {
			[&]()
			{
				if(menu_sel == 0)
				{
					listener->ingameContinueSelected();
				}
				else
				{
					listener->ingameQuitSelected();
				}
				gamepad.left().removeDownHandler();
				gamepad.right().removeDownHandler();
				gamepad.fire().removeUpHandler();
			}
	};
};

#endif
