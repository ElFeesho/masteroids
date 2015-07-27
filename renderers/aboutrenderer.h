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

    void render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const
	{
        gfx.drawRect(120, 70, 403, 300, RGB::BLUE);
        gfx.drawImg(321 - about_width / 2, 81, about_width, about_height, about_img);

		int aboutTextYOffset = 100;
        float textHeight = gfx.measureText("W").h;
        gfx.drawText(false, 145, aboutTextYOffset + textHeight * 6, "MAsteroids for Wii, written by Feesh.", RGB::WHITE);
        gfx.drawText(false, 145, aboutTextYOffset + textHeight * 8, "Thanks go out to:", RGB::WHITE);
        gfx.drawText(false, 180, aboutTextYOffset + textHeight * 10, "Arn` for the cool banner and icon.", RGB::WHITE);
        gfx.drawText(false, 180, aboutTextYOffset + textHeight * 12, "#wiidev IRC channel on Efnet", RGB::WHITE);
        gfx.drawText(false, 180, aboutTextYOffset + textHeight * 14, "Homebrew Channel", RGB::WHITE);
        gfx.drawText(false, 180, aboutTextYOffset + textHeight * 16, "LibOGC and GRRLIB.", RGB::WHITE);
        gfx.drawText(false, 180, aboutTextYOffset + textHeight * 18, "Zaxx and his magical Linux-fu.", RGB::WHITE);
        gfx.drawText(false, 180, aboutTextYOffset + textHeight * 20, "Dare for sucking at Mario Kart", RGB::WHITE);
        gfx.drawText(false, (640 - 22 * font5_char_width) / 2, aboutTextYOffset + textHeight * 22, "Push Start to go back", RGB::WHITE);
	}
};

#endif
