#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "entity.h"
#include "gfx.h"

class GameOver : public Entity
{
public:
	GameOver();
	~GameOver();
	bool update(GfxWrapper *gfx);
private:
	RGB colour;
	RGB colourHighlight;
};

#endif
