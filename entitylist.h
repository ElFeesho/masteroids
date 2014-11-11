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
	Entity *at(int i) { return entities.at(i); }
	int size() { return entities.size(); }
	void clear();

	void checkCollisions(EntityList &otherList, function<void(Entity*, Entity*)> callback);
private:
	vector<Entity*> entities;
};

#endif
