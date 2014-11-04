#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "entity.h"
#include "gfx.h"

class Options : public Entity
{
public:
	Options();
	~Options();
	bool update(GfxWrapper *gfx);
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
	RGB colour;
	RGB colourHighlight;
	Entity *child;
};

#endif
