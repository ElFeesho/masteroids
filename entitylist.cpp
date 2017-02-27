#include "entitylist.h"

#include "entity.h"

bool colliding(Entity &entOne, Entity &entTwo)
{
	double distX = entOne.position().X() - entTwo.position().X();
	double distY = entOne.position().Y() - entTwo.position().Y();
	double hypt = sqrt((distX * distX) + (distY * distY));
	return (hypt < entOne.shape().Radius() + entTwo.shape().Radius());
}


void EntityList::add(std::shared_ptr<Entity> entity) {
	entities.push_back(entity);
}

void EntityList::updateAll()
{
	std::remove_if(entities.begin(), entities.end(), [](std::shared_ptr<Entity> entity){ return !entity->update(); });
}

void EntityList::checkCollisions(Entity &entity, std::function<void(Entity &)> callback)
{
	for (unsigned long i = entities.size(); i >  0; --i)
	{
        if (colliding(*entities.at(i), entity))
		{
            callback(*entities.at(i));
			break;
		}
	}
}

void EntityList::checkCollisions(EntityList &otherList, std::function<void(Entity &, Entity &)> callback)
{
	std::for_each(entities.rbegin(), entities.rend(), [callback, otherList](std::shared_ptr<Entity> leftEntity)
	{
		if (leftEntity->shape() != Shape::NONE && leftEntity->position() != Position::NONE)
		{
			std::for_each(otherList.entities.rbegin(), otherList.entities.rend(), [callback, leftEntity](std::shared_ptr<Entity> rightEntity)
			{
				if (leftEntity->shape() != Shape::NONE && leftEntity->position() != Position::NONE)
				{
					if (colliding(*leftEntity, *rightEntity))
					{
						callback(*leftEntity, *rightEntity);
					}
				}
			});
		}
	});
}

void EntityList::clear()
{
	entities.clear();
}

void EntityList::renderAll(Gfx &gfx)
{
	std::for_each(entities.begin(), entities.end(), [&gfx](std::shared_ptr<Entity> entity) { entity->render(gfx); });
}

void EntityList::removeEntity(std::shared_ptr<Entity> entity)
{
	std::remove_if(entities.begin(), entities.end(), [entity](std::shared_ptr<Entity> currentEntity) { return entity == currentEntity; });
}

std::shared_ptr<Entity> EntityList::at(unsigned long i)
{
    return entities.at(i);
}

unsigned long EntityList::size()
{
    return entities.size();
}

