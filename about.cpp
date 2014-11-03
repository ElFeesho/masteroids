#include "about.h"
#include <ogcsys.h>
#include <gccore.h>

#include "font5.h"
#include "GRRLIB.h"

#include "controlconf.h"

#include "about_img.h"

About::About()
{

}

About::~About()
{

}

bool About::update()
{
	GRRLIB_DrawRectangle(120,70,300, 403, 0x001f,0);
	GRRLIB_DrawImg(321-about_width/2,81,about_width, about_height, about_img, 0.0, 1.0);

   GRRLIB_Print(145, 100+font5_char_high*6, font5_char_width, font5_char_high, (char*)"MAsteroids for Wii, written by Feesh.",font5, 0xffff, 0x0000);
   GRRLIB_Print(145, 100+font5_char_high*8, font5_char_width, font5_char_high, (char*)"Thanks go out to:",font5, 0xffff, 0x0000);
   GRRLIB_Print(180, 100+font5_char_high*10, font5_char_width, font5_char_high, (char*)"Arn` for the cool banner and icon.",font5, 0xffff, 0x0000);
   GRRLIB_Print(180, 100+font5_char_high*12, font5_char_width, font5_char_high, (char*)"#wiidev IRC channel on Efnet",font5, 0xffff, 0x0000);
   GRRLIB_Print(180, 100+font5_char_high*14, font5_char_width, font5_char_high, (char*)"Homebrew Channel",font5, 0xffff, 0x0000);
   GRRLIB_Print(180, 100+font5_char_high*16, font5_char_width, font5_char_high, (char*)"LibOGC and GRRLIB.",font5, 0xffff, 0x0000);
	GRRLIB_Print(180, 100+font5_char_high*18, font5_char_width, font5_char_high, (char*)"Zaxx and his magical Linux-fu.",font5, 0xffff, 0x0000);
	GRRLIB_Print(180, 100+font5_char_high*20, font5_char_width, font5_char_high, (char*)"Dare for sucking at Mario Kart",font5, 0xffff, 0x0000);
   GRRLIB_Print((640-22*font5_char_width)/2, 100+font5_char_high*22, font5_char_width, font5_char_high, (char*)"Push Start to go back",font5, 0xffff, 0x0000);

	if(ControlConf::button_down(0,BUTTON_START))
	{
		return false;
	}

	return true;
}
