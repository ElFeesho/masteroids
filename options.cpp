#include "options.h"
#include "input/gamepadinputmanager.h"
#include "gametime.h"

Options::Options(OptionsListener *listener)
		: optionsRenderer(OptionsRenderer()),
		  listener(listener),
		  alive(true),
		  menu_sel(0),
		  next_change(GameTime::getMillis() + 500),
		  ldir(1),
		  child(NULL),
		  colour(RGB(1.0f, 1.0f, 1.0f)),
		  colourHighlight(RGB(1.0f, 0.8f, 0.0f))
{
	GamepadInputManager::sharedInstance()->inputForPlayer(0)->addListener(this);
}

Options::~Options()
{
	GamepadInputManager::sharedInstance()->inputForPlayer(0)->removeListener(this);
}

bool Options::update()
{
	if (child != NULL)
	{
		if (!child->update())
		{
			delete child;
			child = NULL;
		}
		return true;
	}

	return alive;
}

void Options::render(GfxWrapper *gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}


bool Options::buttonDown(GamepadButton button)
{
	unsigned long cticks = GameTime::getMillis();

	if (button == BUTTON_UP)
	{
		ldir = 0;
		if (menu_sel > 0)
		{
			menu_sel--;
		}
		next_change = GameTime::getMillis() + 500;
	}
	if (button == BUTTON_DOWN)
	{
		ldir = 1;

		if (menu_sel < 6)
		{
			menu_sel++;
		}

		next_change = GameTime::getMillis() + 500;
	}

	if (button == BUTTON_LEFT)
	{
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
	}

	if (button == BUTTON_RIGHT)
	{
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
	}

	if (button == BUTTON_FIRE)
	{
		if (menu_sel == 6)
		{
			//child = new ControlConf();
			listener->optionsControllerConfigSelected();
		}
	}

	optionsRenderer.setMenuSelection(menu_sel);
	return false;
}

bool Options::buttonUp(GamepadButton button)
{
	next_change = 0;
	ldir = -1;

	if (button == BUTTON_START)
	{
		listener->optionsMenuClosed();
		return true;
	}
	return false;
}

int Options::lives = 3;
int Options::difficulty = 1;
bool Options::team_kill = false;
int Options::players = 1;
int Options::max_bullets = 5;
bool Options::music = false;
