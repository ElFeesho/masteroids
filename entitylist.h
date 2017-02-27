#ifndef __ENTITYLIST_H__
#define __ENTITYLIST_H__

#include <vector>
#include <functional>
#include <memory>

class Entity;

class Gfx;

class EntityList
{
public:
	EntityList() {}

	~EntityList() {}

	void add(Entity *entity);

	void updateAll();

    void renderAll(Gfx &gfx);

    void removeEntity(Entity *entity);

    Entity *at(int i);

    int size();

	void clear();

    void checkCollisions(Entity &entity, std::function<void(Entity *)> callback);

    void checkCollisions(EntityList &otherList, std::function<void(Entity *, Entity *)> callback);

private:
    std::vector<std::unique_ptr<Entity>> entities;
};

#endif
