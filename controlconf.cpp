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

ControlConf::ControlConf(ControlConfListener *listener) : listener(listener), menu_sel(0), binding(-1), bind_timeout(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1)
{
	GamepadInputManager::sharedInstance()->playerOne()->addListener(this);
}

ControlConf::~ControlConf()
{	
	GamepadInputManager::sharedInstance()->playerOne()->removeListener(this);
}

void ControlConf::render(GfxWrapper* gfx)
{
	for(int i = 0;i<Options::players;i++)
	{
		char mesg_buf[64] = { 0 };
		char control_name[32] = { 0 };
		
		gfx->drawRect(120, 70, 403, 316, RGB::blue);
		gfx->drawImg(321-controls_width/2,81,controls_width, controls_height, controls_img);
		gfx->drawText(135, 80+font5_char_high*8, "Choose a player using Wiimote or GCN Pad 1", RGB::white);
		gfx->drawText(135, 80+font5_char_high*10, "And then push a button on a controller to",RGB::white);
		gfx->drawText(135, 80+font5_char_high*12, "map it to that player.",RGB::white);

		sprintf(mesg_buf, "Player %d: %s",i+1,control_name);
		if(menu_sel == i)
			gfx->drawText(145, 80+font5_char_high*(15+(i*2)), mesg_buf,RGB::yellow);
		else
			gfx->drawText(145, 80+font5_char_high*(15+(i*2)), mesg_buf,RGB::white);
	}
	gfx->drawText((320-(18*font5_char_width)/2), 80+font5_char_high*25, "Push Start To Exit",RGB::white);
	if(binding!=-1)
	{
		char bind_buf[32] = { 0 };
		sprintf(bind_buf,"Binding Player %d",binding+1);
		gfx->drawText(145, 80+font5_char_high*23, bind_buf,RGB::white);
	}
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