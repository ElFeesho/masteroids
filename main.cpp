
#include "gfx/gfx.h"
#include "gametime.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__

#include <SDL/SDL.h>

#endif

//void ScanPADSandReset(u32 retrace_count)
//{
//
//	PAD_ScanPads();
//	WPAD_ScanPads();
//	//WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
//	if (PAD_ButtonsDown(0) & PAD_TRIGGER_Z)
//	{
//		//exit(0);
//	}
//	//if(!((*(u32*)0xCC003000)>>16))
//	//{
//	//	exit(0);
//	//}
//}

int main(int argc, char **argv)
{
	GfxWrapper *gfxWrapper = new GfxWrapper();
	gfxWrapper->init(640, 480);

	GamepadInputManager::sharedInstance()->initialise();

	ScreenManager screenManager = ScreenManager();
	for (; ;)
	{
		gfxWrapper->waitForVBlank();
		gfxWrapper->fillScreen(RGB::black);

		GamepadInputManager::sharedInstance()->poll();
		screenManager.update(gfxWrapper);
		gfxWrapper->render();
		GameTime::tick();

#ifndef __WII__
		if (GamepadInputManager::sharedInstance()->checkQuit())
		{
			break;
		}

#endif
	}

	return 0;
}
