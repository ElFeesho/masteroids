#ifndef __CONTROL_CONF_H__
#define __CONTROL_CONF_H__

#include "entity.h"
#include "gfx.h"

/* 
	Really complex controller configurator

	Turns out supporting all the devices you can hook up to your wii
	besides one or two is pretty difficult.

	There are several combinations so I hope people can understand why
	this wasn't in the initial release.

	Imagine 1 wiimote and 1 exp
	2 Player is a doddle right?
	1 player uses wiimote, 2 player uses Exp, ok sweet
	Now, we have
	2 wiimotes 1 expansion
	player 1 and 2 use wiimote, player 3 uses expansion

	3 wiimotes 1 expansion, 3 players use wiimote 4th player uses exp

	2wiimotes 2 expansions player 1 uses wiimote player 2 uses wiimote 3 and 4 exps.

	It's hard to program this sort of stuff in automatically.
	How can you tell which player will be holding which device.

	Might not matter too much- it is asteroids after all, but I dunno
	I like it to be polished I guess.

	SIXTEEN input choices. 8 with possible rumble!
*/

#define PLAYER_WIIMOTE_1 1
#define PLAYER_WIIMOTE_2 2
#define PLAYER_WIIMOTE_3 3
#define PLAYER_WIIMOTE_4 4
#define PLAYER_NUNCHUK_1 5
#define PLAYER_NUNCHUK_2 6
#define PLAYER_NUNCHUK_3 7
#define PLAYER_NUNCHUK_4 8
#define PLAYER_CLASSIC_1 9
#define PLAYER_CLASSIC_2 10
#define PLAYER_CLASSIC_3 11
#define PLAYER_CLASSIC_4 12
#define PLAYER_GCNPAD_1  13
#define PLAYER_GCNPAD_2  14
#define PLAYER_GCNPAD_3  15
#define PLAYER_GCNPAD_4  16

#define BUTTON_SHOOT 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 3
#define BUTTON_RIGHT 4
#define BUTTON_UP 5
#define BUTTON_START 6

class ControlConf : public Entity
{
public:
	ControlConf();
	~ControlConf();
	bool update(GfxWrapper *gfx);
	static bool button_down(int player, unsigned int button);
	static bool button_held(int player, unsigned int button);
private:
	int menu_sel;
	int binding;
	unsigned long bind_timeout;
	unsigned long next_change;
	char ldir;
	static int player_controls[4]; // Stores which control the player is going to use
};

#endif
