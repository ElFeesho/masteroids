#include "about.h"
#include <ogcsys.h>
#include <gccore.h>

#include "font5.h"
#include "GRRLIB.h"

#include "controlconf.h"

#include "about_img.h"

About::About() : borderColour(RGB(0.0f, 0.0f, 1.0f)), textColour(RGB(1.0f, 1.0f, 1.0f))
{

}

About::~About()
{

}

bool About::update(GfxWrapper *gfx)
{
	gfx->drawRect(120,70,300, 403, borderColour);
	gfx->drawImg(321-about_width/2,81,about_width, about_height, about_img);

	gfx->drawText(145, 100+font5_char_high*6, (char*)"MAsteroids for Wii, written by Feesh.",textColour);
	gfx->drawText(145, 100+font5_char_high*8, (char*)"Thanks go out to:",textColour);
	gfx->drawText(180, 100+font5_char_high*10, (char*)"Arn` for the cool banner and icon.",textColour);
	gfx->drawText(180, 100+font5_char_high*12, (char*)"#wiidev IRC channel on Efnet",textColour);
	gfx->drawText(180, 100+font5_char_high*14, (char*)"Homebrew Channel",textColour);
	gfx->drawText(180, 100+font5_char_high*16, (char*)"LibOGC and GRRLIB.",textColour);
	gfx->drawText(180, 100+font5_char_high*18, (char*)"Zaxx and his magical Linux-fu.",textColour);
	gfx->drawText(180, 100+font5_char_high*20, (char*)"Dare for sucking at Mario Kart",textColour);
	gfx->drawText((640-22*font5_char_width)/2, 100+font5_char_high*22, (char*)"Push Start to go back",textColour);

	if(ControlConf::button_down(0,BUTTON_START))
	{
		return false;
	}

	return true;
}
