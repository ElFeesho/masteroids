#ifndef __DEBRIS_H__
#define __DEBRIS_H__

#include "entity.h"

class Debris : public Entity
{
public:
	Debris(int amount, double xpos, double ypos, double angle, double xspeed, double yspeed, unsigned short colour, long time_to_live);
	~Debris();
	bool update();
private:
	
	int count;
	double x[16];
	double y[16];
	double angles[16];
	double xsp[16];
	double ysp[16];
	unsigned short col;
	long ttl;
	double rot_speed[16];
	int sizes[16];
	
};

#endif
