#ifndef __ABOUT_H__
#define __ABOUT_H__

#include "entity.h"
#include "gfx.h"

class About : public Entity
{
public:
	About();
	~About();
	bool update(GfxWrapper *gfx);
private:
	RGB borderColour;
	RGB textColour;
};

#endif
