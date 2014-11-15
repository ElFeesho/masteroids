#include "controlconf.h"
#include "input/gamepadinputmanager.h"
#include "gametime.h"

ControlConf::ControlConf(ControlConfListener *listener) : listener(listener), controlConfRenderer(ControlConfRenderer()), menu_sel(0), binding(-1), bind_timeout(0), next_change(GameTime::getMillis()+500), ldir(1)
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

ControlConf::~ControlConf()
{	
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

void ControlConf::render(GfxWrapper* gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}

void ControlConf::buttonDown(GamepadButton button)
{
	
}

void ControlConf::buttonUp(GamepadButton button)
{
	if(button == BUTTON_START)
	{
		listener->controlConfClosed();
	}
}