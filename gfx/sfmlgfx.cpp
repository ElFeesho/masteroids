#ifndef __WII__

#include "sfmlgfx.h"

#include <SFML/Graphics.hpp>
#include <iostream>

RGB RGB::white(1.0f, 1.0f, 1.0f);
RGB RGB::blue(0.0f, 0.5f, 1.0f);
RGB RGB::yellow(1.0f, 5.0f, 0.0f);
RGB RGB::black(0.0f, 0.0f, 0.0f);
RGB RGB::purple(1.0f, 0.0f, 1.0f);
RGB RGB::green(0.0f, 1.0f, 0.0f);

SFMLGfx::SFMLGfx(sf::RenderWindow &window) : app(window)
{
    std::cout << "SFMLGfx" << std::endl;
}

SFMLGfx::~SFMLGfx()
{
    app.close();
    std::cout << "~SFMLGfx" << std::endl;
}


Rect SFMLGfx::measureText(const std::string &text)
{
    return Rect(0, 0, 0, 12*2);
}

void SFMLGfx::drawLine(int x, int y, int x2, int y2, const RGB &colour)
{
    sf::Vertex vertices[] = {
        sf::Vector2f(x*2, y*2), sf::Vector2f(x2*2, y2*2)
    };

    app.draw(vertices, 2, sf::Lines);
}

void SFMLGfx::fillScreen(const RGB &colour)
{
    app.clear(sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB()*255.0f, 255.0f));
}

void SFMLGfx::drawText(bool bold, int x, int y, const std::string &textString, const RGB &colour, TextAlignment align)
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile(bold ? "boldfont.ttf":"regularfont.ttf");
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(2*14);
    text.setColor(sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB() * 255.0f, 255));
    float textSize = text.getLocalBounds().width;
    if(align == TextAlignment::CENTRE)
    {
        text.setPosition(sf::Vector2f((x-textSize/2.0f)*2, y*2));
    }
    else if (align == TextAlignment::RIGHT)
    {
        text.setPosition(sf::Vector2f((x-textSize)*2, y*2));
    }
    else
    {
        text.setPosition(sf::Vector2f(x*2, y*2));
    }

    app.draw(text);
}

void SFMLGfx::drawRect(int x, int y, int w, int h, const RGB &colour)
{
    sf::RectangleShape shape(sf::Vector2f(w*2, h*2));
    shape.setPosition(sf::Vector2f(x*2, y*2));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB() *255.0f, 255));
    app.draw(shape);
}

void SFMLGfx::drawImg(int xpos, int ypos, int width, int height, const unsigned short *data)
{

}

void SFMLGfx::render()
{
    app.display();
}

void SFMLGfx::waitForVBlank()
{

}

#endif


