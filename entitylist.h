#ifndef __ENTITYLIST_H__
#define __ENTITYLIST_H__

#include <vector>
#include <functional>

using std::vector;

using std::function;

class Entity;

class GfxWrapper;

class EntityList
{
public:
	EntityList();

	~EntityList();

	void add(Entity *entity);

	void updateAll();

	void renderAll(GfxWrapper *gfx);

	void removeEntity(Entity *entity)
	{
		for (int i = entities.size() - 1; i >= 0; i--)
		{
			if (entities.at(i) == entity)
			{
				entities.erase(entities.begin() + i);
				return;
			}
		}
	}

	Entity *at(int i)
	{
		return entities.at(i);
	}

	int size()
	{
		return entities.size();
	}

	void clear();

	void checkCollisions(Entity &entity, function<void(Entity *)> callback);

	void checkCollisions(EntityList &otherList, function<void(Entity *, Entity *)> callback);

private:
	vector<Entity *> entities;
};

#endif
