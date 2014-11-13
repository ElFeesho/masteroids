#include <stdio.h>
#include <stdlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp.h>
#include <unistd.h>
#include "music.h"
#include "gfx/gfx.h"
#include "time.h"

#include "input/gamepadinputmanager.h"
#include "screenmanager.h"

#ifndef __WII__
#include <SDL/SDL.h>
#endif

void ScanPADSandReset(u32 retrace_count)
{
	GamepadInputManager::sharedInstance()->poll();
	PAD_ScanPads();
	WPAD_ScanPads();
	//WPAD_ReadPending(WPAD_CHAN_ALL, NULL);
	if(PAD_ButtonsDown(0)&PAD_TRIGGER_Z)
	{
		//exit(0);
	}
	//if(!((*(u32*)0xCC003000)>>16))
	//{
	//	exit(0);
	//}
}

extern u16 *GRRLIB_buffer;

int main(int argc, char **argv)
{
	GfxWrapper *gfxWrapper = new GfxWrapper();
	gfxWrapper->init(640, 480);

	PAD_Init();
	WPAD_Init();
	WPAD_Disconnect(WPAD_CHAN_ALL);
	WPAD_SetIdleTimeout(120);
	
	ScreenManager screenManager = ScreenManager();
	for(;;)
	{
		gfxWrapper->fillScreen(RGB::black);
		VIDEO_WaitVSync();
		ScanPADSandReset(0);
		screenManager.update(gfxWrapper);
		gfxWrapper->render();
		Time::tick();

#ifndef __WII__
		SDL_Event ev = { 0 };

	    while(SDL_PollEvent(&ev))
	    {
		    if(ev.type == SDL_QUIT)
		    {
		        exit(0);
		    }
		}
#endif
	}

	return 0;
}
