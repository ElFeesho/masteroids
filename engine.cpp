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

Engine::Engine(GfxWrapper *wrapper, const RGB &clearColour) :  gfx(wrapper), clearColour(clearColour), pause_ent(NULL), c_level(1), mode(0),lmode(0), last_ufo(0)
{
	ent_list = new vector<Entity *>;
	collent_list = new vector<Collobj *>;
	ent_list_tmp = new vector<Entity *>;
	collent_list_tmp = new vector<Collobj *>;
	start_menu();
}

Engine::~Engine()
{
	clean_up();
}

void Engine::update()
{
	if(pause_ent!=NULL)
	{
		if(!pause_ent->update())
		{
			delete pause_ent;
			pause_ent = NULL;
		}
	}
	else
	{
		gfx->fillScreen(clearColour);
		/* 
			To prevent messing up the entity list during an engine update cycle, a temporary list is created
			so that any entities that need to be added to the update queue are added after the first list of
			entities have finished updating
		*/
		if(ent_list_tmp->size()!=0)
		{
			for(vector<Entity *>::iterator it = ent_list_tmp->begin(); it!=ent_list_tmp->end();it++)
			{
				ent_list->push_back((*it));
			}
			ent_list_tmp->clear();
		}
		if(collent_list_tmp->size()!=0)
		{
			for(vector<Collobj *>::iterator it = collent_list_tmp->begin(); it!=collent_list_tmp->end();it++)
			{
				collent_list->push_back((*it));
			}
			collent_list_tmp->clear();
		}

		for(vector<Entity *>::iterator it = ent_list->begin(); it!=ent_list->end();)
		{
			if(!(*it)->update())
			{
				/* Entity returned false, that means it want's cleaning up */
				delete (*it);
				ent_list->erase(it);
				continue;
			}
			it++;
		}
		for(vector<Collobj *>::iterator it = collent_list->begin(); it!=collent_list->end();)
		{
			if(!(*it)->update())
			{
				/* Entity returned false, that means it want's cleaning up */
				delete (*it);
				collent_list->erase(it);
				continue;
			}
			it++;
		}
		if(mode == 1)
		{
			if(rand()%8192>8000 && ticks_to_millisecs(gettime())>last_ufo+15000)
			{
				last_ufo = ticks_to_millisecs(gettime());
				add_entity(new UFO());
			}
			if(Options::players>1)
			{
				int lcount = 0;
				for(int i = 0; i<Options::players;i++)
				{
					if(!Ship::players[i]) /* Ship hasn't initialised yet! */
					{
						lcount = 1; 
						break;
					}
					lcount+=Ship::players[i]->get_lives();
				}
				if(lcount == 0)
				{
					/* Game over man! */
					mode = 2;
				}
			}
			else
			{ 
				if(Ship::players[0])
					if(!Ship::players[0]->get_lives())
						mode = 2;
			}
			if(Asteroid::count<=0)
			{
				c_level++;
				new_wave();
			}
		}
	}
	if(mode!=lmode) // Game mode has changed
	{
		clean_up();
		if(mode == 0)
		{
			start_menu();
		}
		else if(mode == 1)
		{
			start_game();
		}
		else if(mode == 2)
		{
			start_gameover();
		}
		lmode = mode;
	}
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

