#ifndef __GFX_H__
#define __GFX_H__

#include <string>
#include "resourcemanager.h"

enum TextAlignment
{
	LEFT,
	CENTRE,
	RIGHT
};

class Font
{
public:
	virtual void *getFont() = 0;
};

class RGB
{
public:
	RGB(float r, float g, float b);

	~RGB();

	unsigned int as24bit() const;

	unsigned short as16bit() const;

	float getR() { return r; }
	float getG() { return g; }
	float getB() { return b; }

	static RGB white;
	static RGB blue;
	static RGB yellow;
	static RGB black;
	static RGB purple;
	static RGB green;

private:
	float r;
	float g;
	float b;
};

class GfxWrapper
{
public:
	void init(int w, int h, ResourceManager *resourceManager);

	int textHeight();

	void drawLine(int x, int y, int x2, int y2, const RGB &colour) const;

	void fillScreen(const RGB &colour) const;

	void drawText(bool bold, int x, int y, const std::string &text, const RGB &colour, TextAlignment alignment = LEFT) const;

	void drawRect(int x, int y, int w, int h, const RGB &colour) const;

	void drawImg(int x, int y, int w, int h, const unsigned short *imgData) const;

	void render();

	void waitForVBlank();
private:
	ResourceManager *resourceManager;
};

#endif
