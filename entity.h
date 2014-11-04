#ifndef __ENTITY_H__
#define __ENTITY_H__

class GfxWrapper;

class Engine;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	/* Overridings */
	virtual bool update(GfxWrapper *gfx) = 0;

	double X();
	double X(double nx);
	double Y();
	double Y(double ny);

	Engine *get_engine();
	void set_engine(Engine *handle);
private:
	double x, y;
	
	Engine *eng_handle;
};

#endif
