#ifndef UI_HPP
#define UI_HPP

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <assert.h>
#include <err.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <ctime>
#include <unistd.h>

#define RGB(r,g,b) b|(g<<8)|(r<<16)

class MouseEvent {
	public:
	typedef enum {
		MOUSEDOWN,
		MOUSEMOVE,
		MOUSEDRAG,
	} Type;
	int xPos, yPos;
	signed char xDiff, yDiff;
	unsigned char left, middle, right = 0;
	Type type;
	
	MouseEvent(int x, int y, signed char dx, signed char dy, unsigned char l, unsigned char m, unsigned char r);
};

class MouseListener {
	public:
	void* object;
	void (*handlers[3])(void*, MouseEvent*);

	MouseListener(void* obj);
	void onEvent(MouseEvent* e);
};

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
	int width;
	int height;
	int** bitmap;

	public:
	Canvas(int w, int h);
	void fill(int color);
	void text(int xPos, int yPos, PSFFont* font, const char* str, int fg = 0xffffffff, int bg = 0x00000000);
	void line(int x1, int y1, int x2, int y2, int color);
	void rect(int left, int top, int right, int bottom, int color);
	void roundRect(int left, int top, int right, int bottom, int radius, int color);
	void circle(int xPos, int yPos, int radius, int color);
};

class GraphicsComponent: public Canvas {
	public:
	int xPos;
	int yPos;
	int zPos;
	GraphicsComponent* layers[16];
	MouseListener* mouseListener;
	void (*renderer)(GraphicsComponent*);

	GraphicsComponent(int w, int h);
	GraphicsComponent(int x, int y, int w, int h);
	void render();
	void onMouseEvent(MouseEvent* e);
	void mergeLayers();
};

#endif
