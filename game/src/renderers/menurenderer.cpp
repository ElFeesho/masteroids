#include "menurenderer.h"

void MenuRenderer::setMenuItemSelection(int selection) {
    menu_sel = selection;
}

void MenuRenderer::render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const {
    static float textHeight = gfx.measureText("W").h;

    gfx.drawRect(120, 70, 403, 300, RGB::BLUE);
    gfx.drawImg((640 - asteroid_banner_width) / 2, 80, asteroid_banner_width, asteroid_banner_height, asteroid_banner_data);
    gfx.drawImg(320, 200, controllers_width, controllers_height, controllers_data);

    int menuItemHeight = (int) (textHeight + 15);


    int menuSeparationHeight = 80 + asteroid_banner_height;
    int menuOffsetX = 320 - asteroid_banner_width / 2 + 80;

    if (menu_sel == 0)
    {
        gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight, "Start Game", RGB::YELLOW, TextAlignment::CENTRE);
    }
    else
    {
        gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight, "Start Game", RGB::WHITE, TextAlignment::CENTRE);
    }

    if (menu_sel == 1)
    {
        gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight * 2, "Options", RGB::YELLOW, TextAlignment::CENTRE);
    }
    else
    {
        gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight * 2, "Options", RGB::WHITE, TextAlignment::CENTRE);
    }

    if (menu_sel == 2)
    {
        gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight * 3, "About", RGB::YELLOW, TextAlignment::CENTRE);
    }
    else
    {
        gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight * 3, "About", RGB::WHITE, TextAlignment::CENTRE);
    }

    if (menu_sel == 3)
    {
        gfx.drawText(true, menuOffsetX, menuSeparationHeight + menuItemHeight * 4, "Exit To HBC", RGB::YELLOW, TextAlignment::CENTRE);
    }
    else
    {
        gfx.drawText(false, menuOffsetX, menuSeparationHeight + menuItemHeight * 4, "Exit To HBC", RGB::WHITE, TextAlignment::CENTRE);
    }
    gfx.drawText(false, 320, (int) (80 + asteroid_banner_height + (textHeight + 10) * 10), "Coded by Feesh! - gummybassist@gmail.com", RGB::WHITE, TextAlignment::CENTRE);
}
