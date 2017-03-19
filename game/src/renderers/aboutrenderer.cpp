#include "aboutrenderer.h"

void AboutRenderer::render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const {
    static float textHeight = 0.0f;
    if (textHeight <= 0.0f) {
        textHeight = gfx.measureText("X").h;
    }

    gfx.drawRect(120, 70, 403, 300, RGB::BLUE);
    gfx.drawImg(321 - about_width / 2, 81, about_width, about_height, about_img);

    int aboutTextYOffset = 60;
    gfx.drawText(false, 145, (int)(aboutTextYOffset + textHeight * 6), "MAsteroids for Wii, written by Feesh.", RGB::WHITE);
    gfx.drawText(false, 145, (int)(aboutTextYOffset + textHeight * 7), "Thanks go out to:", RGB::WHITE);
    gfx.drawText(false, 180, (int)(aboutTextYOffset + textHeight * 8), "Arn` for the cool banner and icon.", RGB::WHITE);
    gfx.drawText(false, 180, (int)(aboutTextYOffset + textHeight * 9), "#wiidev IRC channel on Efnet", RGB::WHITE);
    gfx.drawText(false, 180, (int)(aboutTextYOffset + textHeight * 10), "Homebrew Channel", RGB::WHITE);
    gfx.drawText(false, 180, (int)(aboutTextYOffset + textHeight * 11), "LibOGC and GRRLIB.", RGB::WHITE);
    gfx.drawText(false, 180, (int)(aboutTextYOffset + textHeight * 12), "Zaxx and his magical Linux-fu.", RGB::WHITE);
    gfx.drawText(false, 180, (int)(aboutTextYOffset + textHeight * 13), "Dare for sucking at Mario Kart", RGB::WHITE);
    gfx.drawText(false, (640 - 22 * font5_char_width) / 2, (int) (aboutTextYOffset + textHeight * 16), "Push Start to go back", RGB::WHITE);
}

