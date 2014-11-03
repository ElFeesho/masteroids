#ifndef __UFO_H__
#define __UFO_H__

#include "collobj.h"

class UFO : public Collobj
{
public:
	UFO();
	~UFO();
	bool update();
	void on_hit();
private:
	double xspeed;
	double yspeed;
	unsigned long next_think;
	unsigned long next_fire;
	bool alive;
};

#endif
