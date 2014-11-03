#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "entity.h"

class Options : public Entity
{
public:
	Options();
	~Options();
	bool update();
	static int lives;
	static int difficulty;
	static bool team_kill;
	static int players;
	static int max_bullets;
	static bool music;
private:
	int menu_sel;
	unsigned long next_change;
	char ldir;
	Entity *child;
};

#endif
