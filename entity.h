#ifndef __ENTITY_H__
#define __ENTITY_H__

class Engine;

class Entity
{
public:
	Entity();
	~Entity();

	/* Overridings */
	virtual bool update() = 0;

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
