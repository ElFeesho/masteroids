#include "controlconf.h"
#include "input/gamepadinputmanager.h"
#include "gametime.h"

ControlConf::ControlConf(ControlConfListener *listener)
		: listener(listener),
		  controlConfRenderer(ControlConfRenderer()),
		  menu_sel(0),
		  binding(-1),
		  bind_timeout(0),
		  next_change(GameTime::getMillis() + 500),
		  ldir(1)
{

}

ControlConf::~ControlConf()
{
}

void ControlConf::render(Gfx &gfx)
{
	renderer().render(gfx, position(), shape(), direction());
}


void ControlConf::menuScreenPresented() {

}

void ControlConf::menuScreenHidden() {

}
