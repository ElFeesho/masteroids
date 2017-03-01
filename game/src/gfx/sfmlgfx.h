#pragma once

#include <SFML/Graphics.hpp>
#include <gfx/gfx.h>

class SFMLGfx : public Gfx
{
public:
    SFMLGfx(sf::RenderWindow &window);

    virtual Rect measureText(const std::string &text);

    virtual void drawLine(int x, int y, int x2, int y2, const RGB &colour);

    virtual void fillScreen(const RGB &colour);

    virtual void drawText(bool bold, int x, int y, const std::string &text, const RGB &colour, TextAlignment alignment = TextAlignment::LEFT);

    virtual void drawRect(int x, int y, int w, int h, const RGB &colour);

    virtual void drawImg(int x, int y, int w, int h, const unsigned short *imgData);

    virtual void render();

    virtual void waitForVBlank();
private:
    sf::RenderWindow &app;
};
