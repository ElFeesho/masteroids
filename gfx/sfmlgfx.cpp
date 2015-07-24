#ifndef __WII__

#include "gfx.h"

#include <SFML/Graphics.hpp>

#include "../font5.h"

using std::string;

static unsigned int convert16bit_to_24bit(unsigned short colorin)
{
    unsigned char r = (((colorin) & 0x01F) << 3);
    unsigned char g = (((colorin) & 0x03E0) >> 2);
    unsigned char b = (((colorin) & 0x7C00) >> 7);
    return (r << 8) + (g << 16) + (b << 24) + 255;
}

RGB::RGB(float r, float g, float b) : r(r), g(g), b(b)
{
}

RGB::~RGB()
{
}

RGB RGB::white = RGB(1.0f, 1.0f, 1.0f);
RGB RGB::yellow = RGB(1.0f, 0.8f, 0.0f);
RGB RGB::blue = RGB(0.0f, 0.5f, 1.0f);
RGB RGB::black = RGB(0.0f, 0.0f, 0.0f);
RGB RGB::purple = RGB(1.0f, 0.0f, 1.0f);
RGB RGB::green = RGB(0.0f, 1.0f, 0.0f);

static sf::RenderWindow *app;

unsigned int RGB::as24bit() const
{
    int red = 255.0f * r;
    int green = 255.0f * g;
    int blue = 255.0f * b;
    int packed = 0;
    if (red || green || blue)
    {
        packed = 0x000000ff | ((red << 24) | (green << 16) | (blue << 8));
    }
    return packed;
}

unsigned short RGB::as16bit() const
{

    return ((unsigned int) (16 * r)) + (((unsigned int) (32.f * g)) << 5) + (((unsigned int) (16.f * b)) << 11);
}


GfxWrapper::GfxWrapper(const ResourceManager &rsrcMan) : resourceManager{rsrcMan}
{
    app = new sf::RenderWindow(sf::VideoMode(640, 480), "Masteroids");
}

GfxWrapper::~GfxWrapper()
{
    app->close();
}

void GfxWrapper::drawLine(int x, int y, int x2, int y2, const RGB &colour) const
{
    sf::Vertex vertices[] = {
        sf::Vector2f(x, y), sf::Vector2f(x2, y2)
    };
    app->draw(vertices, 2, sf::Lines);

}

void GfxWrapper::fillScreen(const RGB &colour) const
{
    app->clear(sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB()*255.0f, 255.0f));
}

int GfxWrapper::textHeight()
{
    return 10;
}

void GfxWrapper::drawText(bool bold, int x, int y, const string &textString, const RGB &colour, TextAlignment align) const
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile(bold ? "boldfont.ttf":"regularfont.ttf");
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(14);
    text.setColor(sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB() * 255.0f, 255));
    float textSize = text.getLocalBounds().width;
    if(align == CENTRE)
    {
        text.setPosition(sf::Vector2f(x-textSize/2.0f, y));
    }
    else if (align == RIGHT)
    {
        text.setPosition(sf::Vector2f(x-textSize, y));
    }
    else
    {
        text.setPosition(sf::Vector2f(x, y));
    }

    app->draw(text);
}

void GfxWrapper::drawRect(int x, int y, int w, int h, const RGB &colour) const
{
    sf::RectangleShape shape(sf::Vector2f(w, h));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB() *255.0f, 255));
    app->draw(shape);
}

void GfxWrapper::drawImg(int xpos, int ypos, int width, int height, const unsigned short *data) const
{
}

void GfxWrapper::render()
{
    app->display();
}

void GfxWrapper::waitForVBlank()
{

}

#endif
