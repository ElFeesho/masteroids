#ifndef __INGAMEMENURENDERER_H__
#define __INGAMEMENURENDERER_H__

#include "renderer.h"

class GfxWrapper;

class InGameMenuRenderer : public Renderer {
public:
    InGameMenuRenderer();
    ~InGameMenuRenderer();
    void setMenuSelection(int menuSelection);
    void render(GfxWrapper *gfx, Position &position, Shape &shape, Direction &direction, RGB &colour = RGB::white) override;

private:
    int menu_sel;
};

#endif
