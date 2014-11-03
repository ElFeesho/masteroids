#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "entity.h"

class GameOver : public Entity
{
public:
	GameOver();
	~GameOver();
	bool update();
};

#endif
