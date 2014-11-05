#include "gfx.h"

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "font5.h"

static unsigned int convert16bit_to_24bit(unsigned short colorin)
{
    unsigned char r = (((colorin)&0x01F) <<3);
    unsigned char g = (((colorin)&0x03E0) >>2);
    unsigned char b = (((colorin)&0x7C00 )>>7);
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
RGB RGB::blue = RGB(0.0f, 0.0f, 1.0f);
RGB RGB::black = RGB(0.0f, 0.0f, 0.0f);

unsigned int RGB::as24bit() const
{
	int red = 255.0f * r;
	int green = 255.0f * g;
	int blue = 255.0f * b;
	int packed = 0;
	if(red || green || blue)
	{
		packed = 0x000000ff | ((red << 24) | (green << 16) | (blue << 8));
	}
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
	aalineColor(SDL_GetVideoSurface(), x, y, x2, y2, colour.as24bit());
}

void GfxWrapper::fillScreen(const RGB &colour) const
{
	SDL_FillRect(SDL_GetVideoSurface(), NULL, colour.as24bit());
}

void GfxWrapper::drawText(int x, int y, const char *text, const RGB &colour) const
{
	int px,py;
	int ni;
	int i;

	for(i=0; i < strlen(text); i++)
	{	
		ni = (font5_char_width*font5_char_high*(text[i]-1));
		for (py=y;py<y+font5_char_high;py++) 
		{
			for(px=x;px<x+font5_char_width;px++)
			{
				if(font5[ni]!=0xffff)
				{
					pixelColor(SDL_GetVideoSurface(), px+i*font5_char_width, py, colour.as24bit());
				}

				ni++;
			}	
		}
	}
}

void GfxWrapper::drawRect(int x, int y, int w, int h, const RGB &colour) const
{
	rectangleColor(SDL_GetVideoSurface(), x, y, x + w, y + h, colour.as24bit());
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
