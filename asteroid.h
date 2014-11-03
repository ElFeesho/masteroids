#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "collobj.h"

class Asteroid : public Collobj
{
public:
	Asteroid();
	Asteroid(double scale);
	~Asteroid();

	bool update();
	void on_hit();
	static int count;
private:
	double peaks[6];
	double speed;
	bool alive;
	double rot;
	double rot_speed;
	double trav_ang;
};

#endif
