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
	gfx->drawRect(120, 70, 403, 300, RGB::blue);
	gfx->drawImg(321-about_width/2,81,about_width, about_height, about_img);

	int aboutTextYOffset = 100+font5_char_high;

	gfx->drawText(145, aboutTextYOffset*6, "MAsteroids for Wii, written by Feesh.",textColour);
	gfx->drawText(145, aboutTextYOffset*8, "Thanks go out to:",textColour);
	gfx->drawText(180, aboutTextYOffset*10, "Arn` for the cool banner and icon.",textColour);
	gfx->drawText(180, aboutTextYOffset*12, "#wiidev IRC channel on Efnet",textColour);
	gfx->drawText(180, aboutTextYOffset*14, "Homebrew Channel",textColour);
	gfx->drawText(180, aboutTextYOffset*16, "LibOGC and GRRLIB.",textColour);
	gfx->drawText(180, aboutTextYOffset*18, "Zaxx and his magical Linux-fu.",textColour);
	gfx->drawText(180, aboutTextYOffset*20, "Dare for sucking at Mario Kart",textColour);
	gfx->drawText((640-22*font5_char_width)/2, aboutTextYOffset*22, "Push Start to go back",textColour);

	return !(ControlConf::button_down(0,BUTTON_START));
}
