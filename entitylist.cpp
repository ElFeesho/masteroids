#include "entitylist.h"

#include "entity.h"
#include "gfx.h"

EntityList::EntityList()
{

}

EntityList::~EntityList()
{

}

void EntityList::add(Entity *entity)
{
	entities.push_back(entity);
}

void EntityList::updateAll(GfxWrapper *gfx)
{
	for(int i = entities.size()-1; i >= 0; i--)
	{
		if(!entities.at(i)->update(gfx))
		{
			delete entities.at(i);
			entities.erase(entities.begin()+i);
		}
	}
}

void EntityList::clear()
{
	for(int i = entities.size()-1; i >= 0; i--)
	{
		delete entities.at(i);
		entities.erase(entities.begin()+i);
	}
}
