#include <stdio.h>
#include <stdlib.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp.h>
#include <unistd.h>
#include "engine.h"
#include "options.h"
#include "GRRLIB.h"
#include "music.h"

void ScanPADSandReset(u32 retrace_count) 
{
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
	GRRLIB_buffer = GRRLIB_MakeBuffer(640, 480);
	VIDEO_Init();
	GRRLIB_InitVideo();
	GRRLIB_Start();
	PAD_Init();
	WPAD_Init();
	WPAD_Disconnect(WPAD_CHAN_ALL);
	WPAD_SetIdleTimeout(120);

	Engine engine;
	for(;;)
	{
		VIDEO_WaitVSync();
		ScanPADSandReset(0);
		engine.update();
		GRRLIB_Render();
	}

	return 0;
}
