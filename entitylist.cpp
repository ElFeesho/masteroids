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
	for(int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->update(gfx);
	}
}