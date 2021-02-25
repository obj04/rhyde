#pragma once

#include <cmath>
#include "Lock.hpp"
#include "PSFFont.hpp"


class Canvas {
	public:
	int xPos;
	int yPos;
	unsigned int width;
	unsigned int height;
	int* bitmap;
	Lock* lock;

	public:
	Canvas();
	Canvas(unsigned int w, unsigned int h);
	Canvas(int x, int y, unsigned int w, unsigned int h);
	void setPosition(int x, int y);
	bool contains(int x, int y);
	void resize(unsigned int w, unsigned int h);
	int getPixel(int xPos, int yPos);
	void setPixel(int xPos, int yPos, int color);
	void assimilate(int xPos, int yPos, int w, int h, int* layer);
	void assimilate(Canvas* canvas);
	void fill(int color);
	void text(int x, int y, PSFFont* font, const char* str, int fg = 0xffffffff, int bg = 0x00000000);
	void line(int x1, int y1, int x2, int y2, int color);
	void rect(int left, int top, int right, int bottom, int color);
	void roundRect(int left, int top, int right, int bottom, int radius, int color);
	void circle(int xPos, int yPos, int radius, int color);
};
