#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <vector>
#include "entity.h"
#include "collobj.h"
#include "gfx.h"

using std::vector;
/*
	The engine: takes a list of entities and processes them.
*/
class Engine
{
public:
	Engine(GfxWrapper *gfx, const RGB &clearColour );
	~Engine();

	/* Calls all the entities update functions */
	void update();

	/* Add an entity to the ent_list */
	void add_entity(Entity *new_ent);
	void add_entity(Collobj *new_ent);
	
	/* Remove all the entities from ent_list */
	void clean_up();

	vector<Entity *> *get_ents();
	vector<Collobj *> *get_collents();
	void set_mode(int nmode);

	void start_menu();
	void start_game();
	void start_gameover();
	
	void new_wave();
	
	void set_pause_ent(Entity *ent);

private:
	RGB clearColour;
	GfxWrapper *gfx;
	vector<Entity*> *ent_list;
	vector<Collobj *> *collent_list;
	vector<Entity*> *ent_list_tmp;
	vector<Collobj *> *collent_list_tmp;
	Entity *pause_ent;
	int c_level;
	unsigned int mode;
	unsigned int lmode;
	unsigned long last_ufo;
};

#endif
