#ifndef __ABOUT_RENDERER_H__
#define __ABOUT_RENDERER_H__

#include "../images/about_img.h"
#include "../font5.h"
#include "renderer.h"
#include "../gfx/gfx.h"

class AboutRenderer : public Renderer
{
public:
	AboutRenderer()
	{
	}

	~AboutRenderer()
	{
	}

    void render(GfxWrapper &gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white)
	{
        gfx.drawRect(120, 70, 403, 300, RGB::blue);
        gfx.drawImg(321 - about_width / 2, 81, about_width, about_height, about_img);

		int aboutTextYOffset = 100;

        gfx.drawText(false, 145, aboutTextYOffset + gfx.textHeight() * 6, "MAsteroids for Wii, written by Feesh.", RGB::white);
        gfx.drawText(false, 145, aboutTextYOffset + gfx.textHeight() * 8, "Thanks go out to:", RGB::white);
        gfx.drawText(false, 180, aboutTextYOffset + gfx.textHeight() * 10, "Arn` for the cool banner and icon.", RGB::white);
        gfx.drawText(false, 180, aboutTextYOffset + gfx.textHeight() * 12, "#wiidev IRC channel on Efnet", RGB::white);
        gfx.drawText(false, 180, aboutTextYOffset + gfx.textHeight() * 14, "Homebrew Channel", RGB::white);
        gfx.drawText(false, 180, aboutTextYOffset + gfx.textHeight() * 16, "LibOGC and GRRLIB.", RGB::white);
        gfx.drawText(false, 180, aboutTextYOffset + gfx.textHeight() * 18, "Zaxx and his magical Linux-fu.", RGB::white);
        gfx.drawText(false, 180, aboutTextYOffset + gfx.textHeight() * 20, "Dare for sucking at Mario Kart", RGB::white);
        gfx.drawText(false, (640 - 22 * font5_char_width) / 2, aboutTextYOffset + gfx.textHeight() * 22, "Push Start to go back", RGB::white);
	}
};

#endif
