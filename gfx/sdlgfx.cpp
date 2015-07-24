#ifndef __WII__

#include "gfx.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
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

SDL_Color fromRGB(RGB colour)
{
	SDL_Color returnVal = { .r = (Uint8)(colour.getR() * 255.0f),
									.g = (Uint8)(colour.getG() * 255.0f),
									.b = (Uint8)(colour.getB() * 255.0f),
									.unused = 0};
	return returnVal;
}


GfxWrapper::GfxWrapper(const ResourceManager &rsrcMan) : resourceManager{rsrcMan}
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw "Couldn't initialise SDL";
    }

    SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
}

GfxWrapper::~GfxWrapper()
{
    SDL_Quit();
}

void GfxWrapper::drawLine(int x, int y, int x2, int y2, const RGB &colour) const
{
	aalineColor(SDL_GetVideoSurface(), x, y, x2, y2, colour.as24bit());
}

void GfxWrapper::fillScreen(const RGB &colour) const
{
	SDL_FillRect(SDL_GetVideoSurface(), NULL, colour.as24bit());
}

int GfxWrapper::textHeight()
{
	return font5_char_high;
}

void GfxWrapper::drawText(bool bold, int x, int y, const string &text, const RGB &colour, TextAlignment align) const
{
	TTF_Font *font = nullptr;
    font = (TTF_Font *) (bold ? resourceManager.boldFont().getFont() : resourceManager.regularFont().getFont());

	int textSize;
	int unused;
	TTF_SizeText(font, text.c_str(), &textSize, &unused);

	if (align == CENTRE)
	{
		x -= textSize / 2;
	}
	else if (align == RIGHT)
	{
		x -= textSize;
	}

    SDL_Rect dstRect = { .x = (Sint16)x, .y = (Sint16)y, .w = (Uint16)textSize, .h = (Uint16)unused };
	SDL_Surface *pSurface = TTF_RenderText_Blended(font, text.c_str(), fromRGB(colour));
	SDL_BlitSurface(pSurface, NULL, SDL_GetVideoSurface(), &dstRect);
	SDL_FreeSurface(pSurface);
}

void GfxWrapper::drawRect(int x, int y, int w, int h, const RGB &colour) const
{
	rectangleColor(SDL_GetVideoSurface(), x, y, x + w, y + h, colour.as24bit());
}

void GfxWrapper::drawImg(int xpos, int ypos, int width, int height, const unsigned short *data) const
{
	int x, y;
	int ni = 0;
	for (y = ypos; y < ypos + height; y++)
	{
		for (x = xpos; x < xpos + width; x++)
		{
			if (data[ni] != 0xf00f)
			{
				pixelColor(SDL_GetVideoSurface(), x, y, convert16bit_to_24bit(data[ni]));
			}
			ni++;
		}
	}
}

void GfxWrapper::render()
{
	SDL_Flip(SDL_GetVideoSurface());
}

void GfxWrapper::waitForVBlank()
{
	static long lastTicks = 0;
	long currentTime = SDL_GetTicks();
	if (currentTime - lastTicks < (1000 / 60))
	{
		SDL_Delay((1000 / 60) - (currentTime - lastTicks));
	}
	lastTicks = SDL_GetTicks();
}

#endif
