#ifndef __COLOBJ_H__
#define __COLOBJ_H__

#include "entity.h"

class Collobj : public Entity
{
public:
	Collobj();
	~Collobj();
	virtual void on_hit() = 0;
	void set_radius(double nradius);
	double get_radius();
private:
	double radius;
};

#endif
