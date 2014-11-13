#include "about.h"
#include <ogcsys.h>
#include <gccore.h>

#include "font5.h"

#include "about_img.h"

#include "input/gamepadinputmanager.h"

About::About(AboutListener *listener) : aboutRenderer(AboutRenderer()), listener(listener)
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

About::~About()
{
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

void About::render(GfxWrapper* gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

void About::buttonDown(GamepadButton button)
{

}

void About::buttonUp(GamepadButton button)
{
	if(button == BUTTON_FIRE || button == BUTTON_START)
	{
		listener->aboutClosed();
	}
}
