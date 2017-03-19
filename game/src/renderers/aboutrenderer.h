#ifndef __ABOUT_RENDERER_H__
#define __ABOUT_RENDERER_H__

#include "../images/about_img.h"
#include "../font5.h"
#include "renderer.h"
#include <gfx/gfx.h>

class AboutRenderer : public Renderer
{
public:
    void render(Gfx &gfx, Position &, Shape &, Direction &, RGB &) const;
};

#endif
