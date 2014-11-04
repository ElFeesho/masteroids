#ifndef __GFX_H__
#define __GFX_H__

class RGB
{
public:
	RGB(float r, float g, float b);
	~RGB();

	unsigned int as24bit() const;
	unsigned short as16bit() const;

private:
	float r;
	float g;
	float b;
};

class GfxWrapper
{
public:
	void init(int w, int h);

	void drawLine(int x, int y, int x2, int y2, const RGB &colour) const;
	void fillScreen(const RGB &colour) const;
	void drawText(int x, int y, const char *text, const RGB &colour) const;
	void drawRect(int x, int y, int w, int h, const RGB &colour) const;

	void render();
};

#endif