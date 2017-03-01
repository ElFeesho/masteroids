#ifndef __WII__

#include "sfmlgfx.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#ifdef MACOSX
#include "resources.h"
#endif

RGB RGB::WHITE(1.0f, 1.0f, 1.0f);
RGB RGB::BLUE(0.0f, 0.5f, 1.0f);
RGB RGB::YELLOW(1.0f, 5.0f, 0.0f);
RGB RGB::BLACK(0.0f, 0.0f, 0.0f);
RGB RGB::PURPLE(1.0f, 0.0f, 1.0f);
RGB RGB::GREEN(0.0f, 1.0f, 0.0f);

SFMLGfx::SFMLGfx(sf::RenderWindow &window) : app(window)
{
}

Rect SFMLGfx::measureText(const std::string &inputText)
{
    sf::Text text;
    sf::Font font;
#ifdef MACOSX
    font.loadFromFile(Resources::regularFontLocation());
#else
    font.loadFromFile("regularfont.ttf");
#endif
    text.setFont(font);
    text.setString(inputText);
    text.setCharacterSize(2*14);
    const sf::FloatRect &rect = text.getLocalBounds();

    return Rect(0, 0, rect.width, rect.height);
}

void SFMLGfx::drawLine(int x, int y, int x2, int y2, const RGB &colour)
{

    sf::Vertex vertices[] = {
            sf::Vertex(sf::Vector2f(x*2, y*2), sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB()*255.0f)), sf::Vertex(sf::Vector2f(x2*2, y2*2),sf::Color(colour.getR()*255.0f, colour.getG()*255.0f, colour.getB()*255.0f))
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
#ifdef MACOSX
    font.loadFromFile(bold ? Resources::boldFontLocation():Resources::regularFontLocation());
#else
    font.loadFromFile(bold ? "boldfont.ttf":"regularfont.ttf");
#endif
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

void SFMLGfx::drawImg(int x, int y, int w, int h, const unsigned short *pixels)
{
    static std::map<const unsigned short *, sf::Texture> textureLookup;

    if (textureLookup.find(pixels) == textureLookup.end()) {
        sf::Uint8* pixels_32bit = new sf::Uint8[w * h * 4];
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                unsigned short cpixel = pixels[w*i + j];
                unsigned char red = (cpixel & 0xf800) >> 11;
                unsigned char green = (cpixel & 0x07e0) >> 5;
                unsigned char blue = cpixel & 0x001f;

                pixels_32bit[(w*i*4)+j*4 + 0] = (int)((red/31.f)*255.f);
                pixels_32bit[(w*i*4)+j*4 + 1] = (int)((green/63.f)*255.f);
                pixels_32bit[(w*i*4)+j*4 + 2] = (int)((blue/31.f)*255.f);
                pixels_32bit[(w*i*4)+j*4 + 3] = 255;
            }
        }
        sf::Texture texture;
        texture.create(w, h);
        texture.update(pixels_32bit);
        textureLookup[pixels] = texture;
        texture.setSmooth(true);
    }

    sf::Sprite sprite;
    sprite.setTexture(textureLookup[pixels]);
    sprite.setScale(sf::Vector2f(2.0f, 2.0f));
    sprite.move(sf::Vector2f(x*2, y*2));

    app.draw(sprite);
}

void SFMLGfx::render()
{
    app.display();
}

void SFMLGfx::waitForVBlank()
{

}

#endif


