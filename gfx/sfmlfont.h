#pragma once

#include <SFML/Graphics.hpp>
#include "gfx/gfx.h"

class SFMLFont : public Font
{
public:
    SFMLFont(const char *name, int size);

    ~SFMLFont();

    void *getFont() const;

private:

};
