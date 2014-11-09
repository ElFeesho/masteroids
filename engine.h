#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <vector>
#include "entity.h"
#include "gfx.h"
#include "screenmanager.h"

using std::vector;
/*
	The engine: takes a list of entities and processes them.
*/
class Engine
{
public:
	Engine(ScreenManager *screenManager);
	~Engine();

	/* Calls all the entities update functions */
	void update(GfxWrapper *gfx);


private:
	ScreenManager *screenManager;
};

#endif
