#include "entitylist.h"

#include "entity.h"
#include "gfx.h"
#include <cmath>

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

void EntityList::updateAll()
{
	for(int i = entities.size()-1; i >= 0; i--)
	{
		if(!entities.at(i)->update())
		{
			delete entities.at(i);
			entities.erase(entities.begin()+i);
		}
	}
}

void EntityList::checkCollisions(EntityList &otherList, function<void(Entity*, Entity*)> callback)
{
	for(int i = 0; i < entities.size(); i++)
	{
		if(!(entities.at(i)->shape() == Shape::NONE || entities.at(i)->position() == Position::NONE))
		{
			for(int j = 0; j < otherList.size(); j++)
			{
				Entity *entOne = entities.at(i);
				Entity *entTwo = otherList.at(i);
				double distX = entOne->position().X() - entTwo->position().X();
				double distY = entOne->position().Y() - entTwo->position().Y();
				double hypt = sqrt((distX * distX) + (distY * distY));
				if(hypt < entOne->shape().Radius() + entTwo->shape().Radius())
				{
					callback(entOne, entTwo);
				}
			}
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
void EntityList::renderAll(GfxWrapper* gfx){
	for(int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->render(gfx);
	}
}
