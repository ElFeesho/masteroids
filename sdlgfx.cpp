#include "gfx.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

RGB::RGB(float r, float g, float b) : r(r), g(g), b(b)
{

}

RGB::~RGB()
{

}

RGB RGB::white = RGB(1.0f, 1.0f, 1.0f);
RGB RGB::yellow = RGB(1.0f, 0.8f, 0.0f);
RGB RGB::blue = RGB(0.0f, 0.0f, 1.0f);

unsigned int RGB::as24bit() const
{
	int red = 255.0f * r;
	int green = 255.0f * g;
	int blue = 255.0f * b;
	int packed = 0xff000000 | (red << 16) | (green << 8) | (blue) ;
	return packed;
}

unsigned short RGB::as16bit() const
{
	return ((unsigned int)(16 * r)) + ((unsigned int)(32.f * g))<<5 + ((unsigned int)(16.f * b))<<11;	
}

void GfxWrapper::init(int w, int h)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE);
}

void GfxWrapper::drawLine(int x, int y, int x2, int y2, const RGB &colour) const
{
	lineColor(SDL_GetVideoSurface(), x, y, x2, y2, colour.as24bit());
}

void GfxWrapper::fillScreen(const RGB &colour) const
{
	SDL_FillRect(SDL_GetVideoSurface(), NULL, colour.as24bit());
}

void GfxWrapper::drawText(int x, int y, const char *text, const RGB &colour) const
{

}

void GfxWrapper::drawRect(int x, int y, int w, int h, const RGB &colour) const
{
	rectangleColor(SDL_GetVideoSurface(), x, y, x+w, h, colour.as24bit());
}

void GfxWrapper::drawImg(int xpos, int ypos, int width, int height, const unsigned short *data) const
{
	int x, y;
	int ni = 0;
	for(y=ypos;y<ypos+height;y++)
	{
        for(x=xpos;x<xpos+width;x++)
        {
			if(data[ni]!=0xf00f)
			{
            	pixelColor(SDL_GetVideoSurface(), x, y, data[ni]);
            }
            ni++;
        }
	}	
}

void GfxWrapper::render()
{
	SDL_Flip(SDL_GetVideoSurface());
}
