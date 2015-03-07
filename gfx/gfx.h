#ifndef __GFX_H__
#define __GFX_H__

#include <string>

enum TextAlignment
{
	LEFT,
	CENTRE,
	RIGHT
};

class RGB
{
public:
	RGB(float r, float g, float b);

	~RGB();

	unsigned int as24bit() const;

	unsigned short as16bit() const;

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
	void init(int w, int h);

	int textHeight();

	void drawLine(int x, int y, int x2, int y2, const RGB &colour) const;

	void fillScreen(const RGB &colour) const;

	void drawText(int x, int y, const std::string &text, const RGB &colour, TextAlignment alignment = LEFT) const;

	void drawRect(int x, int y, int w, int h, const RGB &colour) const;

	void drawImg(int x, int y, int w, int h, const unsigned short *imgData) const;

	void render();
};

#endif
