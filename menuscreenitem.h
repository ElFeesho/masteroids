#pragma once

#include "entity.h"

class MenuScreenItem : public Entity
{
public:
    virtual ~MenuScreenItem() {};
    virtual void menuScreenPresented() = 0;
    virtual void menuScreenHidden() = 0;
};
