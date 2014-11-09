#ifndef __ENTITY_H__
#define __ENTITY_H__

class GfxWrapper;

class Engine;

class Entity
{
public:
	Entity(){};
	virtual ~Entity() {};

	virtual bool update() = 0;
	virtual void render(GfxWrapper *gfx) = 0;

	double X();
	double X(double nx);
	double Y();
	double Y(double ny);
private:
	double x, y;
};

#endif
