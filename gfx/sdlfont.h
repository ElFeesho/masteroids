#pragma once

#include <SDL/SDL_ttf.h>
#include "gfx/gfx.h"

class SDLFont : public Font
{
public:
    SDLFont(const char *name, int size);

    ~SDLFont();

    void *getFont() const;

private:
    TTF_Font *ttfFont;
};
