#pragma once

#include <vector>
#include "gfx/gfx.h"
#include "entity.h"

class Screen
{
public:
	virtual ~Screen()
	{
    }

    virtual void update(Gfx &gfx) = 0;

	virtual void screenShown() = 0;

	virtual void screenHidden() = 0;
};
