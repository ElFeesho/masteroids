#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"
#include "gfx.h"

class InGame : public Entity
{
public:
	InGame(int player);
	~InGame();
	bool update(GfxWrapper *gfx);
private:
	int player_num;
	int menu_sel;
	RGB colour;
	RGB colourHighlight;
};

#endif
