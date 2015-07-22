#include "gfx/sdlfont.h"

SDLFont::SDLFont(const char *name, int size)
{
    TTF_Init();
    ttfFont = TTF_OpenFont(name, size);
    if (ttfFont == nullptr)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    printf("SDLFont CTOR\n");
}

SDLFont::~SDLFont()
{
    printf("SDLFont DTOR\n");
    TTF_CloseFont(ttfFont);
}

void *SDLFont::getFont() const
{
    return ttfFont;
}
