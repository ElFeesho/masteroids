#include "gfx.h"

#include <ogcsys.h>

#include <string.h>
#include <strings.h>
#include <grrlib.h>
#include <stdlib.h>

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

void *buffer = 0;

void GfxWrapper::init(int w, int h)
{
	//buffer = GRRLIB_MakeBuffer(w, h);
	GRRLIB_Init();
}

void GfxWrapper::drawLine(int x, int y, int x2, int y2, const RGB &colour) const
{
	GRRLIB_Line(x, y, x2, y2, colour.as24bit());
}

void GfxWrapper::fillScreen(const RGB &colour) const
{
	GRRLIB_FillScreen(colour.as16bit());
}

int GfxWrapper::textHeight()
{
	return font5_char_high;
}

void GfxWrapper::drawText(int x, int y, const string &text, const RGB &colour, TextAlignment align) const
{
	//GRRLIB_Print(x, y, 9, 2816 / 256, (char*)text.c_str(), font5, colour.as16bit(), 0);
}

void GfxWrapper::drawRect(int x, int y, int w, int h, const RGB &colour) const
{
	GRRLIB_Rectangle(x, y, w, h, colour.as24bit(), 0);
}

void GfxWrapper::drawImg(int xpos, int ypos, int width, int height, const unsigned short *data) const
{
	//GRRLIB_DrawImg(xpos, ypos, width, height, data, 0, 0);
}

void GfxWrapper::render()
{
	GRRLIB_Render();
}

void GfxWrapper::waitForVBlank()
{
	VIDEO_WaitVSync();
}
