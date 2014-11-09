#ifndef __ENTITYLIST_H__
#define __ENTITYLIST_H__

#include <vector>

using std::vector;

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
	void clear();
private:
	vector<Entity*> entities;
};

#endif