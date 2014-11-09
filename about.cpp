#include "about.h"
#include <ogcsys.h>
#include <gccore.h>

#include "font5.h"

#include "about_img.h"

About::About() : alive(true)
{

}

About::~About()
{

}

bool About::update()
{
	return alive;
}

void About::render(GfxWrapper* gfx)
{
	gfx->drawRect(120, 70, 403, 300, RGB::blue);
	gfx->drawImg(321-about_width/2,81,about_width, about_height, about_img);

	int aboutTextYOffset = 100+font5_char_high;

	gfx->drawText(145, aboutTextYOffset*6, "MAsteroids for Wii, written by Feesh.",RGB::white);
	gfx->drawText(145, aboutTextYOffset*8, "Thanks go out to:",RGB::white);
	gfx->drawText(180, aboutTextYOffset*10, "Arn` for the cool banner and icon.",RGB::white);
	gfx->drawText(180, aboutTextYOffset*12, "#wiidev IRC channel on Efnet",RGB::white);
	gfx->drawText(180, aboutTextYOffset*14, "Homebrew Channel",RGB::white);
	gfx->drawText(180, aboutTextYOffset*16, "LibOGC and GRRLIB.",RGB::white);
	gfx->drawText(180, aboutTextYOffset*18, "Zaxx and his magical Linux-fu.",RGB::white);
	gfx->drawText(180, aboutTextYOffset*20, "Dare for sucking at Mario Kart",RGB::white);
	gfx->drawText((640-22*font5_char_width)/2, aboutTextYOffset*22, "Push Start to go back",RGB::white);
}

void About::buttonDown(GamepadButton button)
{

}

void About::buttonUp(GamepadButton button)
{
	if(button == BUTTON_FIRE || button == BUTTON_START)
	{
		alive = false;
	}
}
