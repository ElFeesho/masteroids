#ifndef __WII__

#include "resourcemanager.h"
#include "gfx.h"

ResourceManager::ResourceManager(const Font &boldFont, const Font &regularFont) : _regularFont(regularFont), _boldFont(boldFont)
{
    printf("ResourceManager::CTOR\n");
}

ResourceManager::~ResourceManager()
{
    printf("ResourceManager::DTOR\n");
}

const Font &ResourceManager::boldFont() const
{
	return _boldFont;
}

const Font &ResourceManager::regularFont() const
{
	return _regularFont;
}

#endif
