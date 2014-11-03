#ifndef __INGAME_H__
#define __INGAME_H__

#include "entity.h"

class InGame : public Entity
{
public:
	InGame(int player);
	~InGame();
	bool update();
private:
	int player_num;
	int menu_sel;
	
};

#endif
