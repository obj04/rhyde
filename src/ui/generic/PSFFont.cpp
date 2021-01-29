#include "../UI.hpp"


PSFFont::PSFFont(unsigned char* data) {
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

bool** PSFFont::getGlyph(unsigned char c)
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
