#include "gfx.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

RGB::RGB(float r, float g, float b) : r(r), g(g), b(b)
{

}

RGB::~RGB()
{

}

unsigned int RGB::as24bit() const
{
	return (((unsigned int)(255.0f * r)) + ((unsigned int)(255.0f * g))<<8 + ((unsigned int)(255.0f * b))<<16) + 0xff000000;
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
	rectangleColor(SDL_GetVideoSurface(), x, y, x+w, y+h, colour.as24bit());
}

void GfxWrapper::render()
{
	SDL_Flip(SDL_GetVideoSurface());
}
