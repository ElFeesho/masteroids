#include <vector>
#include <ogc/lwp_watchdog.h>
#include <stdlib.h>
#include "engine.h"
#include "ship.h"
#include "asteroid.h"
#include "options.h"
#include "collobj.h"
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
Engine::Engine(ScreenManager *screenManager) : screenManager(screenManager), pause_ent(NULL), c_level(1), mode(0),lmode(0), last_ufo(0)
{
	ent_list = new vector<Entity *>;
	collent_list = new vector<Collobj *>;
	ent_list_tmp = new vector<Entity *>;
	collent_list_tmp = new vector<Collobj *>;
}

Engine::~Engine()
{
	clean_up();
}

void Engine::update(GfxWrapper *gfx)
{
	screenManager->update(gfx);
}

void Engine::add_entity(Entity *new_ent)
{
	new_ent->set_engine(this);
	ent_list_tmp->push_back(new_ent);
}

void Engine::add_entity(Collobj *new_ent)
{
	new_ent->set_engine(this);
	collent_list_tmp->push_back(new_ent);
}

void Engine::clean_up()
{
	
	for(vector<Entity *>::iterator it = ent_list_tmp->begin(); it!=ent_list_tmp->end();)
	{
		/* Entity returned false, that means it want's cleaning up */
		delete (*it);
		ent_list_tmp->erase(it);
	}
	for(vector<Collobj *>::iterator it = collent_list_tmp->begin(); it!=collent_list_tmp->end();)
	{
		/* Entity returned false, that means it want's cleaning up */
		delete (*it);
		collent_list_tmp->erase(it);
	}
	for(vector<Entity *>::iterator it = ent_list->begin(); it!=ent_list->end();)
	{
		/* Entity returned false, that means it want's cleaning up */
		delete (*it);
		ent_list->erase(it);
	}
	for(vector<Collobj *>::iterator it = collent_list->begin(); it!=collent_list->end();)
	{
		/* Entity returned false, that means it want's cleaning up */
		delete (*it);
		collent_list->erase(it);
	}
	for(int i = 0; i<4; i++)
		Ship::players[i] = NULL;

	Asteroid::count = 0;
}

vector<Entity *> *Engine::get_ents()
{
	return ent_list;
}

vector<Collobj *> *Engine::get_collents()
{
	return collent_list;
}

void Engine::new_wave()
{
	for(int i = 0; i<c_level * 2 + 5;i++)
		add_entity(new Asteroid());
}

void Engine::set_mode(int nmode)
{
	mode = nmode;
}

void Engine::set_pause_ent(Entity *ent)
{
	pause_ent = ent;
	ent->set_engine(this);
}

void Engine::start_menu()
{
	clean_up();
	add_entity(new Menu());
	for(int i = 0; i<15;i++)
		add_entity(new Asteroid());	
}

void Engine::start_game()
{
	clean_up();
	for(int i = 0;i<Options::players;i++)
		add_entity(new Ship(i));
	new_wave();	
}

void Engine::start_gameover()
{
	clean_up();
	add_entity(new GameOver());
}

