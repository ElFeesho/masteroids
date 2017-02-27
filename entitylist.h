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

	void add(std::shared_ptr<Entity> entity);

	void updateAll();

    void renderAll(Gfx &gfx);

    void removeEntity(std::shared_ptr<Entity> entity);

    std::shared_ptr<Entity> at(unsigned long i);

    unsigned long size();

	void clear();

    void checkCollisions(Entity &entity, std::function<void(Entity &)> callback);

    void checkCollisions(EntityList &otherList, std::function<void(Entity &, Entity &)> callback);

private:
    std::vector<std::shared_ptr<Entity>> entities;
};

#endif
