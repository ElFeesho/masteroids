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

	bool update();

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
        return alwaysAliveMonitor;
	}

	Renderer &renderer()
	{
		return pauseDialogRenderer;
	}

private:
    AlwaysAlive alwaysAliveMonitor;
	GamepadSource &gamepad;
	PauseDialogListener *listener;
	PauseDialogRenderer pauseDialogRenderer;
	int menu_sel;
	std::function<void()> leftHandler{
			[&]()
			{
				menu_sel = 0;
				pauseDialogRenderer.setMenuSelection(menu_sel);
			}
	};

	std::function<void()> rightHandler{
			[&]()
			{
				menu_sel = 1;
				pauseDialogRenderer.setMenuSelection(menu_sel);
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
                gamepad.left().removeDownHandler(&leftHandler);
                gamepad.right().removeDownHandler(&rightHandler);
                gamepad.fire().removeUpHandler(&fireHandler);
			}
	};
};

#endif
