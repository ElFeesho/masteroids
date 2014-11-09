#include <vector>
#include <ogc/lwp_watchdog.h>
#include <stdlib.h>
#include "engine.h"
#include "ship.h"
#include "asteroid.h"
#include "options.h"
#include "menu.h"
#include "gameover.h"
#include <gccore.h>
#include <ogcsys.h>
#include "GRRLIB.h"
#include "controlconf.h"
#include "UFO.h"
#include "gfx.h"

using std::vector;

/* Engine Class Implementation */
Engine::Engine(ScreenManager *screenManager) : screenManager(screenManager)
{
}

Engine::~Engine()
{
}

void Engine::update(GfxWrapper *gfx)
{
	screenManager->update(gfx);
}
