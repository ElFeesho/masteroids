#ifndef __WII__

#include "sfmlgfx.h"

#include <iostream>

#ifdef MACOSX
#include "resources.h"
const int scale = 2;
#else
const int scale = 1;
#endif

RGB RGB::WHITE(1.0f, 1.0f, 1.0f);
RGB RGB::BLUE(0.0f, 0.5f, 1.0f);
RGB RGB::YELLOW(1.0f, 5.0f, 0.0f);
RGB RGB::BLACK(0.0f, 0.0f, 0.0f);
RGB RGB::PURPLE(1.0f, 0.0f, 1.0f);
RGB RGB::GREEN(0.0f, 1.0f, 0.0f);

static inline sf::Color fromColour(const RGB &colour) {
    return sf::Color((sf::Uint8) (colour.getR() * 255.f), (sf::Uint8) (colour.getG() * 255.f), (sf::Uint8) (colour.getB() * 255.f), 255);
}

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
        sf::Vertex(sf::Vector2f(x*scale, y*scale), fromColour(colour)),
        sf::Vertex(sf::Vector2f(x2*scale, y2*scale),fromColour(colour))
    };

    app.draw(vertices, 2, sf::Lines);
}

void SFMLGfx::fillScreen(const RGB &colour)
{
    app.clear(fromColour(colour));
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
    text.setFillColor(fromColour(colour));
    float textSize = text.getLocalBounds().width;
    if(align == TextAlignment::CENTRE)
    {
        text.setPosition(sf::Vector2f((x-textSize/2.0f)*scale, y*scale));
    }
    else if (align == TextAlignment::RIGHT)
    {
        text.setPosition(sf::Vector2f((x-textSize)*scale, y*scale));
    }
    else
    {
        text.setPosition(sf::Vector2f(x*scale, y*scale));
    }

    app.draw(text);
}

void SFMLGfx::drawRect(int x, int y, int w, int h, const RGB &colour)
{
    sf::RectangleShape shape(sf::Vector2f(w*scale, h*scale));
    shape.setPosition(sf::Vector2f(x*scale, y*scale));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(5);
    shape.setOutlineColor(fromColour(colour));
    app.draw(shape);
}

void SFMLGfx::drawImg(int x, int y, unsigned int w, unsigned int h, const unsigned short *pixels)
{
    static std::map<const unsigned short *, sf::Texture> textureLookup;

    if (textureLookup.find(pixels) == textureLookup.end()) {
        sf::Uint8* pixels_32bit = new sf::Uint8[w * h * 4];
        for(unsigned int i = 0; i < h; i++)
        {
            for(unsigned int j = 0; j < w; j++)
            {
                unsigned short cpixel = pixels[w*i + j];
                unsigned char red = (unsigned char) ((cpixel & 0xf800) >> 11);
                unsigned char green = (unsigned char) ((cpixel & 0x07e0) >> 5);
                unsigned char blue = (unsigned char) (cpixel & 0x001f);

                pixels_32bit[(w*i*4)+j*4 + 0] = (sf::Uint8) ((red / 31.f) * 255.f);
                pixels_32bit[(w*i*4)+j*4 + 1] = (sf::Uint8) ((green / 63.f) * 255.f);
                pixels_32bit[(w*i*4)+j*4 + 2] = (sf::Uint8) ((blue / 31.f) * 255.f);
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
    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.move(sf::Vector2f(x*scale, y*scale));

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


