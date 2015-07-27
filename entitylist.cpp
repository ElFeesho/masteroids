#include "entitylist.h"

#include "entity.h"

bool colliding(Entity *entOne, Entity *entTwo)
{
	double distX = entOne->position().X() - entTwo->position().X();
	double distY = entOne->position().Y() - entTwo->position().Y();
	double hypt = sqrt((distX * distX) + (distY * distY));
	return (hypt < entOne->shape().Radius() + entTwo->shape().Radius());
}

void EntityList::add(Entity *entity)
{
    entities.emplace_back(entity);
}

void EntityList::updateAll()
{
	for (int i = entities.size() - 1; i >= 0; i--)
	{
		if (!entities.at(i)->update())
		{
			entities.erase(entities.begin() + i);
		}
	}
}

void EntityList::checkCollisions(Entity &entity, std::function<void(Entity *)> callback)
{
	for (int i = entities.size() - 1; i >= 0; i--)
	{
        if (colliding(entities.at(i).get(), &entity))
		{
            callback(entities.at(i).get());
			break;
		}
	}
}

void EntityList::checkCollisions(EntityList &otherList, std::function<void(Entity *, Entity *)> callback)
{
	for (int i = entities.size() - 1; i >= 0; i--)
	{
        if (!(entities.at(i).get()->shape() == Shape::NONE || entities.at(i)->position() == Position::NONE))
		{
			for (int j = otherList.size() - 1; j >= 0; j--)
			{
                if (colliding(entities.at(i).get(), otherList.at(j)))
				{
                    callback(entities.at(i).get(), otherList.at(j));
					break;
				}
			}
		}
	}
}

void EntityList::clear()
{
	for (int i = entities.size() - 1; i >= 0; i--)
	{
        entities.erase(entities.begin() + i);
	}
}

void EntityList::renderAll(Gfx &gfx)
{
	for (int i = 0; i < entities.size(); i++)
	{
		entities.at(i)->render(gfx);
	}
}

void EntityList::removeEntity(Entity *entity)
{
    for (int i = entities.size() - 1; i >= 0; i--)
    {
        if (entities.at(i).get() == entity)
        {
            entities.erase(entities.begin() + i);
            return;
        }
    }
}

Entity *EntityList::at(int i)
{
    return entities.at(i).get();
}

int EntityList::size()
{
    return entities.size();
}
