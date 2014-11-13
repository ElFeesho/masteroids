#include <ogcsys.h>
#include <gccore.h>
#include <cstdio>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include "controlconf.h"

#include "controls_img.h"

using std::sprintf;

#include "GRRLIB.h"
#include "font5.h"

#include "options.h"
#include "gamepadinputmanager.h"

ControlConf::ControlConf(ControlConfListener *listener) : listener(listener), controlConfRenderer(ControlConfRenderer()), menu_sel(0), binding(-1), bind_timeout(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1)
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