#pragma once

#include <string>

enum class TextAlignment
{
	LEFT,
	CENTRE,
	RIGHT
};

class Font
{
public:
    virtual void *getFont() const = 0;
};

class RGB
{
public:
    RGB(float red, float green, float blue) : r(red), g(green), b(blue) {
    }

    unsigned int as24bit() const {
        int redF = 255.0f * r;
        int greenF = 255.0f * g;
        int blueF = 255.0f * b;
        int packed = 0;

        if (redF || greenF || blueF)
        {
            packed = 0x000000ff | ((redF << 24) | (greenF << 16) | (blueF << 8));
        }
        return packed;
    }

    unsigned short as16bit() const {
        return ((unsigned int) (16.f * r)) + (((unsigned int) (32.f * g)) << 5) + (((unsigned int) (16.f * b)) << 11);
    }

    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }

    static RGB WHITE;
	static RGB BLUE;
	static RGB YELLOW;
	static RGB BLACK;
	static RGB PURPLE;
	static RGB GREEN;

private:
	float r;
	float g;
	float b;
};

struct Rect
{
    float x;
    float y;
    float w;
    float h;

    Rect(float xPos, float yPos, float width, float height) : x(xPos), y(yPos), w(width), h(height) {}
};

class Gfx
{
public:

    virtual ~Gfx() {}

    virtual Rect measureText(const std::string &string) = 0;

    virtual void drawLine(int x, int y, int x2, int y2, const RGB &colour) = 0;

    virtual void fillScreen(const RGB &colour) = 0;

    virtual void drawText(bool bold, int x, int y, const std::string &text, const RGB &colour, TextAlignment alignment = TextAlignment::LEFT) = 0;

    virtual void drawRect(int x, int y, int w, int h, const RGB &colour) = 0;

    virtual void drawImg(int x, int y, int w, int h, const unsigned short *imgData) = 0;

    virtual void render() = 0;

    virtual void waitForVBlank() = 0;
private:
};
