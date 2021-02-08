#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define RGB(r,g,b) b|(g<<8)|(r<<16)


class PSFFont {
	static const uint32_t PSF2Magic = 0x864AB572;
	typedef struct {
		uint32_t magic;
		uint32_t version;
		uint32_t headerSize;
		uint32_t flags;
		uint32_t glyphCount;
		uint32_t glyphSize;
		uint32_t glyphHeight;
		uint32_t glyphWidth;
	} PSF2Header;
	PSF2Header header;
	unsigned char** glyphs;

	public:
	unsigned int& width = header.glyphWidth;
	unsigned int& height = header.glyphHeight;

	public:
	PSFFont(unsigned char* data);	
	bool** getGlyph(unsigned char c);
};

class Canvas {
	public:
	unsigned int width;
	unsigned int height;
	int* bitmap;

	public:
	Canvas(unsigned int w, unsigned int h);
	void resize(unsigned int w, unsigned int h);
	int getPixel(int xPos, int yPos);
	void setPixel(int xPos, int yPos, int color);
	void fill(int color);
	void text(int x, int y, PSFFont* font, const char* str, int fg = 0xffffffff, int bg = 0x00000000);
	void assimilate(int xPos, int yPos, int w, int h, int* layer);
	void line(int x1, int y1, int x2, int y2, int color);
	void rect(int left, int top, int right, int bottom, int color);
	void roundRect(int left, int top, int right, int bottom, int radius, int color);
	void circle(int xPos, int yPos, int radius, int color);
};

class LayeredCanvas: public Canvas {
	public:
	int xPos;
	int yPos;

	LayeredCanvas(unsigned int w, unsigned int h);
	LayeredCanvas(int x, int y, unsigned int w, unsigned int h);
	bool contains(int x, int y);
};
