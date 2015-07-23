#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "entity.h"
#include "input/gamepad.h"
#include "gfx/gfx.h"
#include "menuscreenitem.h"

#include <string.h>

#include "renderers/optionsrenderer.h"
#include "gametime.h"

class OptionsListener
{
public:
	virtual ~OptionsListener()
	{
	};

	virtual void optionsControllerConfigSelected() = 0;

	virtual void optionsMenuClosed() = 0;
};

class Options : public MenuScreenItem
{
public:
	Options(OptionsListener *listener);

	~Options();

	bool update();

    void render(GfxWrapper &gfx);

    void menuScreenPresented() override;
    void menuScreenHidden() override;

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
		return optionsRenderer;
	}

	static int lives;
	static int difficulty;
	static bool team_kill;
	static int players;
	static int max_bullets;
	static bool music;
private:
    AlwaysAlive alwaysAliveMonitor;
	OptionsListener *listener;
	OptionsRenderer optionsRenderer;
	bool alive;
	int menu_sel;
	unsigned long next_change;
	char ldir;
    Entity *child;
	RGB colour;
    RGB colourHighlight;

	std::function<void()> upPressedHandler { [&](){
		ldir = 0;
		if (menu_sel > 0)
		{
			menu_sel--;
		}

		optionsRenderer.setMenuSelection(menu_sel);
		next_change = GameTime::getMillis() + 500;
	}};

	std::function<void()> leftPressedHandler { [&](){
		unsigned long cticks = GameTime::getMillis();

		if (ldir == 2)
		{
			next_change = cticks + 200;
		}
		else
		{
			next_change = cticks + 500;
		}
		ldir = 2;
		switch (menu_sel)
		{
			case 0: // Lives
				if (Options::lives > 1)
				{
					Options::lives--;
				}
				break;
			case 1: // Difficulty
				if (Options::difficulty > 0)
				{
					Options::difficulty--;
				}
				break;
			case 2: // Team killing
				Options::team_kill = false;
				break;
			case 3: // Players
				if (Options::players > 1)
				{
					Options::players--;
				}
				break;
			case 4: // Max Bullets
				if (Options::max_bullets > 1)
				{
					Options::max_bullets--;
				}
				break;
			case 5: // Music
				Options::music = false;
				break;
		}
	}};

	std::function<void()> rightPressedHandler { [&](){
		unsigned long cticks = GameTime::getMillis();

		if (ldir == 3)
		{
			next_change = cticks + 200;
		}
		else
		{
			next_change = cticks + 500;
		}
		ldir = 3;

		switch (menu_sel)
		{
			case 0: // Lives
				if (Options::lives < 9)
				{
					Options::lives++;
				}
				break;
			case 1: // Difficulty
				if (Options::difficulty < 2)
				{
					Options::difficulty++;
				}
				break;
			case 2: // Team killing
				if (!Options::team_kill)
				{
					Options::team_kill = true;
				}
				break;
			case 3: // Players
				if (Options::players < 4)
				{
					Options::players++;
				}
				break;
			case 4: // Max Bullets
				if (Options::max_bullets < 10)
				{
					Options::max_bullets++;
				}
				break;
			case 5: // Music
				Options::music = true;
				break;
		}
	}};

	std::function<void()> downPressedHandler { [&](){
		ldir = 1;

		if (menu_sel < 6)
		{
			menu_sel++;
		}

		optionsRenderer.setMenuSelection(menu_sel);
		next_change = GameTime::getMillis() + 500;
	}};

	std::function<void()> firePressed { [&](){
		if (menu_sel == 6)
		{
			//child = new ControlConf();
			listener->optionsControllerConfigSelected();
		}
	}};

	std::function<void()> pausePressed { [&](){
		listener->optionsMenuClosed();
	}};

	std::function<void()> buttonReleased { [&](){
		next_change = 0;
		ldir = -1;
	}};
};

#endif
