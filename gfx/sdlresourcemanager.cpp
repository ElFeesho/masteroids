#ifndef __WII__
#include "resourcemanager.h"
#include "gfx.h"

#include <SDL/SDL_ttf.h>

class SDLFont : public Font
{
public:
	SDLFont(const char *name, int size) : ttfFont(TTF_OpenFont(name, size))
	{
		if (ttfFont == nullptr)
		{
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}

	}

	~SDLFont()
	{
		TTF_CloseFont(ttfFont);
	}

	void *getFont()
	{
		return ttfFont;
	}

private:
	TTF_Font *ttfFont;
};

ResourceManager::ResourceManager()
{
    printf("CTOR ResourceManager\n");
	TTF_Init();
	_regularFont = new SDLFont("regularfont.ttf", 16);
	_boldFont = new SDLFont("boldfont.ttf", 16);
}

ResourceManager::~ResourceManager()
{
    printf("Resource manager dtor\n");
}

Font *ResourceManager::boldFont() const
{
	return _boldFont;
}

Font *ResourceManager::regularFont() const
{
	return _regularFont;
}

#endif
