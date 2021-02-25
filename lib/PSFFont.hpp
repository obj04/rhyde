#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
