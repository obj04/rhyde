#ifndef PSFFONT
#define PSFFONT

#include <assert.h>
#include <err.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sysexits.h>
#include <ctime>
#include <unistd.h>


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
	PSFFont(unsigned char* data) {
		memcpy(&header, data, sizeof(header));
		if (header.magic != PSF2Magic) {
			errx(
				EX_DATAERR, "invalid header magic %08X",
				header.magic
			);
		}
		if (header.headerSize != sizeof(PSF2Header)) {
			errx(
				EX_DATAERR, "weird header size %d",
				header.headerSize
			);
		}
		
		glyphs = new unsigned char*[128];
		for(int i = 0; i < 128; i++) {
			glyphs[i] = new unsigned char[header.glyphSize];
			memcpy(glyphs[i], (data + header.headerSize + header.glyphSize * i), header.glyphSize);
		}
	}
	
	bool** getGlyph(unsigned char c)
	{
		int width = header.glyphWidth;
		int height = header.glyphHeight;
		bool** bitmap = new bool*[height];
		for(int i = 0; i < height; i++)
			bitmap[i] = new bool[width];
		
		for(int i = 0; i < width * height; i++) {
			int y = i / width;
			int x = i % width;
			bitmap[y][x] = (glyphs[c][i / 8] >> (7 - (i % 8))) % 2;
		}
		return bitmap;
	}
};

#endif
