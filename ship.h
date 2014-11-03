#ifndef __SHIP_H__
#define __SHIP_H__

#include "collobj.h"

class Ship : public Collobj
{
public:
	Ship();
	Ship(int padnum);
	~Ship();
	void inc_bfired();
	void dec_bfired();
	bool update();
	void add_score(int am);
	void on_hit();
	void draw_lives();
	int get_lives();
	int get_score();
	static Ship *players[4];
	static int scores[4];
private:
	int player_num;
	double rot; /* Ship Rot */
	double angle;	/* Travel Angle */
	double xspeed, yspeed;
	int bullets_fired;
	int score;
	int llevel;
	int lives;
	unsigned long kill_time;
	unsigned short colour;
};

#endif
