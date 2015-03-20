#include "resourcemanager.h"
#include "gfx.h"
#include <grrlib.h>

#include "boldfont.h"
#include "regularfont.h"

class GRRLIBFont : public Font
{
public:
	GRRLIBFont(const unsigned char *fontName, unsigned int length) : font(GRRLIB_LoadTTF(fontName, length)) {
		printf("Loaded font: %p\n", font);
	}
	~GRRLIBFont()
	{
		GRRLIB_FreeTTF(font);
	}
	void *getFont()
	{
		printf("FONT: %p\n", font);
		return font;
	}
private:
	GRRLIB_ttfFont *font;
};

ResourceManager::ResourceManager()
{
	_boldFont = new GRRLIBFont(bold, bold_size);
	_regularFont = new GRRLIBFont(regularfont, regularfont_size);
}

ResourceManager::~ResourceManager()
{
	delete _boldFont;
	delete _regularFont;
}

Font *ResourceManager::boldFont()
{
	return _boldFont;
}

Font *ResourceManager::regularFont()
{
	return _regularFont;
}