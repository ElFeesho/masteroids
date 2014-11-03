#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "entity.h"

class About : public Entity
{
public:
	About();
	~About();
	bool update();
};

#endif
