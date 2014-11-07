#include <ogcsys.h>
#include <gccore.h>
#include <cstdio>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include "controlconf.h"

#include "controls_img.h"

using std::sprintf;

#include "GRRLIB.h"
#include "font5.h"

#include "options.h"

ControlConf::ControlConf() : menu_sel(0), binding(-1), bind_timeout(0), next_change(ticks_to_millisecs(gettime())+500), ldir(1)
{

}

ControlConf::~ControlConf()
{

}

bool ControlConf::update(GfxWrapper *gfx)
{

	gfx->drawRect(120,70,316, 403, RGB::blue);
	gfx->drawImg(321-controls_width/2,81,controls_width, controls_height, controls_img);
	gfx->drawText(135, 80+font5_char_high*8, "Choose a player using Wiimote or GCN Pad 1", RGB::white);
	gfx->drawText(135, 80+font5_char_high*10, "And then push a button on a controller to",RGB::white);
	gfx->drawText(135, 80+font5_char_high*12, "map it to that player.",RGB::white);

	for(int i = 0;i<Options::players;i++)
	{
		char mesg_buf[64] = { 0 };
		char control_name[32] = { 0 };
		switch(player_controls[i])
		{
			case PLAYER_WIIMOTE_1:
				sprintf(control_name,"Wiimote 1");
				break;
			case PLAYER_WIIMOTE_2:
				sprintf(control_name,"Wiimote 2");
				break;
			case PLAYER_WIIMOTE_3:
				sprintf(control_name,"Wiimote 3");
				break;
			case PLAYER_WIIMOTE_4:
				sprintf(control_name,"Wiimote 4");
				break;
			case PLAYER_NUNCHUK_1:
				sprintf(control_name,"Nunchuk 1");
				break;
			case PLAYER_NUNCHUK_2:
				sprintf(control_name,"Nunchuk 2");
				break;
			case PLAYER_NUNCHUK_3:
				sprintf(control_name,"Nunchuk 3");
				break;
			case PLAYER_NUNCHUK_4:
				sprintf(control_name,"Nunchuk 4");
				break;
			case PLAYER_CLASSIC_1:
				sprintf(control_name,"Classic Controller 1");
				break;
			case PLAYER_CLASSIC_2:
				sprintf(control_name,"Classic Controller 2");
				break;
			case PLAYER_CLASSIC_3:
				sprintf(control_name,"Classic Controller 3");
				break;
			case PLAYER_CLASSIC_4:
				sprintf(control_name,"Classic Controller 4");
				break;
			case PLAYER_GCNPAD_1:
				sprintf(control_name,"Gamecube Pad 1");
				break;
			case PLAYER_GCNPAD_2:
				sprintf(control_name,"Gamecube Pad 2");
				break;
			case PLAYER_GCNPAD_3:
				sprintf(control_name,"Gamecube Pad 3");
				break;
			case PLAYER_GCNPAD_4:
				sprintf(control_name,"Gamecube Pad 4");
				break;
		}
		sprintf(mesg_buf, "Player %d: %s",i+1,control_name);
		if(menu_sel == i)
			gfx->drawText(145, 80+font5_char_high*(15+(i*2)), mesg_buf,RGB::yellow);
		else
			gfx->drawText(145, 80+font5_char_high*(15+(i*2)), mesg_buf,RGB::white);
	}
	gfx->drawText((320-(18*font5_char_width)/2), 80+font5_char_high*25, "Push Start To Exit",RGB::white);
	if(binding!=-1)
	{
		char bind_buf[32] = { 0 };
		sprintf(bind_buf,"Binding Player %d",binding+1);
		gfx->drawText(145, 80+font5_char_high*23, bind_buf,RGB::white);
	}

	if(button_down(0,BUTTON_START))
		return false;

	if(binding==-1)
	{
		unsigned long cticks = ticks_to_millisecs(gettime());
		if(button_held(0,BUTTON_UP) && menu_sel>0 && cticks>next_change)
		{
			if(ldir == 0)
				next_change = cticks+200;
			else
				next_change = cticks+500;
			ldir = 0;
			menu_sel--;
		}
		if(button_held(0,BUTTON_DOWN) && menu_sel<Options::players-1 && cticks>next_change)
		{
			if(ldir == 1)
				next_change = cticks+200;
			else
				next_change = cticks+500;
			ldir = 1;
			menu_sel++;
		}

		if(!button_held(0,BUTTON_UP) && ldir == 0)
		{
			next_change = 0;
		}
		if(!button_held(0,BUTTON_DOWN) && ldir == 1)
		{
			next_change = 0;
		}
		if(button_down(0,BUTTON_SHOOT))
		{
			binding = menu_sel;
			bind_timeout = ticks_to_millisecs(gettime())+300;
		}
	}
	else if(ticks_to_millisecs(gettime())>bind_timeout)
	{
		for(int i = 0; i<4; i++)
		{
			if(PAD_ButtonsDown(i)&(0xffff^(PAD_BUTTON_DOWN|PAD_BUTTON_UP|PAD_BUTTON_LEFT|PAD_BUTTON_RIGHT)))
			{
				for(int j = 0;j<Options::players;j++)
				{
					if(j!=menu_sel)
						if(player_controls[j] == PLAYER_GCNPAD_1+i)
						{
							player_controls[j] = player_controls[binding];
							break;
						}
				}
				player_controls[binding] = PLAYER_GCNPAD_1+i;
				binding = -1;
				break;
			}

			if(WPAD_ButtonsDown(i)&(0xffff^(WPAD_BUTTON_DOWN|WPAD_BUTTON_UP|WPAD_BUTTON_LEFT|WPAD_BUTTON_RIGHT)))
			{
				for(int j = 0;j<Options::players;j++)
				{
					if(j!=menu_sel)
						if(player_controls[j] == PLAYER_WIIMOTE_1+i)
						{
							player_controls[j] = player_controls[binding];
							break;
						}
				}
				player_controls[binding] = PLAYER_WIIMOTE_1+i;
				binding = -1;
				break;
			}

			expansion_t exp;
			WPAD_Expansion(i,&exp);
			if(exp.type!=WPAD_EXP_NONE)
			{
				if(exp.type==WPAD_EXP_NUNCHUK)
				{
					if(exp.nunchuk.btns&0xffffffff)
					{
						for(int j = 0;j<Options::players;j++)
						{
							if(j!=binding)
								if(player_controls[j] == PLAYER_NUNCHUK_1+i)
								{
									player_controls[j] = player_controls[binding];
									break;
								}
						}
						player_controls[binding] = PLAYER_NUNCHUK_1+i;
						binding = -1;
						break;
					}
				}
				else if(exp.type==WPAD_EXP_CLASSIC)
				{
					if(exp.classic.btns & 0xffffffff)
					{
						for(int j = 0;j<Options::players;j++)
						{
							if(j!=binding)
								if(player_controls[j] == PLAYER_CLASSIC_1+i)
								{
									player_controls[j] = player_controls[binding];
									break;
								}
						}
						player_controls[binding] = PLAYER_CLASSIC_1+i;
						binding = -1;
						break;
					}
				}
			}
		}
	}
	return true;
}

bool ControlConf::button_down(int player, u32 button)
{
	expansion_t exp;

	switch(player_controls[player])
	{
		case PLAYER_GCNPAD_1:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsDown(0)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsDown(0)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsDown(0)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsDown(0)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsDown(0)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsDown(0)&PAD_BUTTON_START)
					return true;
			break;
		case PLAYER_GCNPAD_2:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsDown(1)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsDown(1)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsDown(1)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsDown(1)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsDown(1)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsDown(1)&PAD_BUTTON_START)
					return true;
			break;
		case PLAYER_GCNPAD_3:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsDown(2)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsDown(2)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsDown(2)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsDown(2)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsDown(2)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsDown(2)&PAD_BUTTON_START)
					return true;
			break;
		case PLAYER_GCNPAD_4:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsDown(3)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsDown(3)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsDown(3)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsDown(3)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsDown(3)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsDown(3)&PAD_BUTTON_START)
					return true;
			break;

		case PLAYER_WIIMOTE_1:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsDown(0)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsDown(0)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsDown(0)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsDown(0)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsDown(0)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsDown(0)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_WIIMOTE_2:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsDown(1)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsDown(1)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsDown(1)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsDown(1)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsDown(1)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsDown(1)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_WIIMOTE_3:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsDown(2)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsDown(2)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsDown(2)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsDown(2)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsDown(2)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsDown(2)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_WIIMOTE_4:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsDown(3)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsDown(3)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsDown(3)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsDown(3)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsDown(3)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsDown(3)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_1:
			WPAD_Expansion(0,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(0)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsDown(0)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsDown(0)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsDown(0)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsDown(0)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(0)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_2:
			expansion_t exp;
			WPAD_Expansion(1,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(1)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsDown(1)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsDown(1)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsDown(1)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsDown(1)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(1)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_3:
			WPAD_Expansion(2,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(2)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsDown(2)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsDown(2)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsDown(2)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsDown(2)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(2)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_4:
			WPAD_Expansion(3,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(3)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsDown(3)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsDown(3)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsDown(3)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsDown(3)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(3)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_NUNCHUK_1:
			WPAD_Expansion(0,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(0)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(0)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
		case PLAYER_NUNCHUK_2:
			WPAD_Expansion(1,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(1)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(1)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
		case PLAYER_NUNCHUK_3:
			WPAD_Expansion(2,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(2)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(2)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
		case PLAYER_NUNCHUK_4:
			WPAD_Expansion(3,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsDown(3)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>=0.9)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsDown(3)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
	}
	return false;
}

bool ControlConf::button_held(int player, u32 button)
{
	expansion_t exp;

	switch(player_controls[player])
	{
		case PLAYER_GCNPAD_1:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsHeld(0)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsHeld(0)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsHeld(0)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsHeld(0)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsHeld(0)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsHeld(0)&PAD_BUTTON_START)
					return true;
			break;
		case PLAYER_GCNPAD_2:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsHeld(1)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsHeld(1)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsHeld(1)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsHeld(1)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsHeld(1)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsHeld(1)&PAD_BUTTON_START)
					return true;
			break;
		case PLAYER_GCNPAD_3:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsHeld(2)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsHeld(2)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsHeld(2)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsHeld(2)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsHeld(2)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsHeld(2)&PAD_BUTTON_START)
					return true;
			break;
		case PLAYER_GCNPAD_4:
			if(button==BUTTON_SHOOT)
				if(PAD_ButtonsHeld(3)&PAD_BUTTON_A)
					return true;
			if(button==BUTTON_LEFT)
				if(PAD_ButtonsHeld(3)&PAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_RIGHT)
				if(PAD_ButtonsHeld(3)&PAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_DOWN)
				if(PAD_ButtonsHeld(3)&PAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_UP)
				if(PAD_ButtonsHeld(3)&PAD_BUTTON_UP)
					return true;
			if(button==BUTTON_START)
				if(PAD_ButtonsHeld(3)&PAD_BUTTON_START)
					return true;
			break;

		case PLAYER_WIIMOTE_1:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsHeld(0)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_WIIMOTE_2:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(1)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsHeld(1)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(1)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsHeld(1)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsHeld(1)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsHeld(1)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_WIIMOTE_3:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(2)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsHeld(2)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(2)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsHeld(2)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsHeld(2)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsHeld(2)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_WIIMOTE_4:
			if(button==BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(3)&WPAD_BUTTON_2)
					return true;
			if(button==BUTTON_LEFT)
				if(WPAD_ButtonsHeld(3)&WPAD_BUTTON_UP)
					return true;
			if(button==BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(3)&WPAD_BUTTON_DOWN)
					return true;
			if(button==BUTTON_DOWN)
				if(WPAD_ButtonsHeld(3)&WPAD_BUTTON_LEFT)
					return true;
			if(button==BUTTON_UP)
				if(WPAD_ButtonsHeld(3)&WPAD_BUTTON_RIGHT)
					return true;
			if(button==BUTTON_START)
				if(WPAD_ButtonsHeld(3)&WPAD_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_1:
			WPAD_Expansion(0,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(0)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsHeld(0)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(0)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsHeld(0)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsHeld(0)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(0)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_2:
			expansion_t exp;
			WPAD_Expansion(1,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(1)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsHeld(1)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(1)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsHeld(1)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsHeld(1)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(1)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_3:
			WPAD_Expansion(2,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(2)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsHeld(2)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(2)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsHeld(2)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsHeld(2)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(2)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_CLASSIC_4:
			WPAD_Expansion(3,&exp);
			if(exp.type != WPAD_EXP_CLASSIC)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(3)&WPAD_CLASSIC_BUTTON_A)
					return true;
			if(button == BUTTON_LEFT)
				if(WPAD_ButtonsHeld(3)&WPAD_CLASSIC_BUTTON_LEFT)
					return true;
			if(button == BUTTON_RIGHT)
				if(WPAD_ButtonsHeld(3)&WPAD_CLASSIC_BUTTON_RIGHT)
					return true;
			if(button == BUTTON_DOWN)
				if(WPAD_ButtonsHeld(3)&WPAD_CLASSIC_BUTTON_DOWN)
					return true;
			if(button == BUTTON_UP)
				if(WPAD_ButtonsHeld(3)&WPAD_CLASSIC_BUTTON_UP)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(3)&WPAD_CLASSIC_BUTTON_PLUS)
					return true;
			break;
		case PLAYER_NUNCHUK_1:
			WPAD_Expansion(0,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(0)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(0)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
		case PLAYER_NUNCHUK_2:
			WPAD_Expansion(1,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(1)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(1)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
		case PLAYER_NUNCHUK_3:
			WPAD_Expansion(2,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(2)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(2)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
		case PLAYER_NUNCHUK_4:
			WPAD_Expansion(3,&exp);
			if(exp.type != WPAD_EXP_NUNCHUK)
				return false;
			if(button == BUTTON_SHOOT)
				if(WPAD_ButtonsHeld(3)&WPAD_NUNCHUK_BUTTON_Z)
					return true;
			if(button == BUTTON_LEFT)
				if((exp.nunchuk.js.ang>=270-45 && exp.nunchuk.js.ang<=270+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_RIGHT)
				if((exp.nunchuk.js.ang>=90-45 && exp.nunchuk.js.ang<=90+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_DOWN)
				if((exp.nunchuk.js.ang>=180-45 && exp.nunchuk.js.ang<=180+45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_UP)
				if((exp.nunchuk.js.ang>=315 || exp.nunchuk.js.ang<=45) && exp.nunchuk.js.mag>0.5)
					return true;
			if(button == BUTTON_START)
				if(WPAD_ButtonsHeld(3)&WPAD_NUNCHUK_BUTTON_C)
					return true;
			break;
	}
	return false;
}
int ControlConf::player_controls[4] = { PLAYER_GCNPAD_1, PLAYER_WIIMOTE_2, PLAYER_WIIMOTE_3, PLAYER_WIIMOTE_4 };
