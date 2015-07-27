#pragma once

#include <string>
#include "resourcemanager.h"

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
    RGB(float r, float g, float b) : r(r), g(g), b(b) {}

    ~RGB() {}

    unsigned int as24bit() const {
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

    unsigned short as16bit() const {
        return ((unsigned int) (16 * r)) + (((unsigned int) (32.f * g)) << 5) + (((unsigned int) (16.f * b)) << 11);
    }

    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }

    static RGB white;
	static RGB blue;
	static RGB yellow;
	static RGB black;
	static RGB purple;
	static RGB green;

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

    Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
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
