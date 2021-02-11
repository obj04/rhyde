#include "Graphics.hpp"


Canvas::Canvas(unsigned int w, unsigned int h) {
	lock = new Lock();
	width = w;
	height = h;
	bitmap = new int[height * width];
}

void Canvas::resize(unsigned int w, unsigned int h) {
	int* old = bitmap;
	lock->acquire();
	bitmap = new int[h * w];
	delete old;
	width = w;
	height = h;
	lock->release();
}

int Canvas::getPixel(int yPos, int xPos) {
	long long pos = yPos * width + xPos;
	if(pos < 0) return 0;
	if(pos >= height * width) return 0;
	return bitmap[pos];
}

void Canvas::setPixel(int yPos, int xPos, int color) {
	long long pos = yPos * width + xPos;
	if(pos < 0) return;
	if(pos >= height * width) return;
	bitmap[pos] = color;
}

void Canvas::fill(int color) {
	rect(0, 0, width, height, color);
}

void Canvas::text(int xPos, int yPos, PSFFont* font, const char* str, int fg, int bg) {
	bool** glyph;
	for(int i = 0; i < strlen(str); i++) {
		glyph = font->getGlyph(str[i]);
		for(int y = 0; y < font->height; y++)
			for(int x = 0; x < font->width; x++) {
				if(glyph[y][x])
					setPixel(yPos + y, xPos + i * font->width + x, fg);
				else
					setPixel(yPos + y, xPos + i * font->width + x, bg);
			}
	}
}

void Canvas::assimilate(int xPos, int yPos, int w, int h, int* layer) {
	int pixelY, pixelX;
	unsigned int currentColor, layerColor;
	unsigned char currentAlpha, layerAlpha;
	unsigned char r, g, b;
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			pixelX = xPos + x;
			pixelY = yPos + y;
			layerColor = layer[y * w + x];
			currentColor = getPixel(pixelY, pixelX);
			layerAlpha = layerColor >> 24 % 256;
			currentAlpha = 255 - layerAlpha; //currentColor >> 24 % 256;
			if(layerAlpha == 0)
				continue;
			if(layerAlpha == 255) {
				setPixel(pixelY, pixelX, layerColor);
				continue;
			}
			r = (((currentColor >> 16) % 256) * currentAlpha + ((layerColor >> 16) % 256) * layerAlpha) / (layerAlpha + currentAlpha);
			g = (((currentColor >> 8) % 256) * currentAlpha + ((layerColor >> 8) % 256) * layerAlpha) / (layerAlpha + currentAlpha);
			b = ((currentColor % 256) * currentAlpha + (layerColor % 256) * layerAlpha) / (layerAlpha + currentAlpha);
			setPixel(pixelY, pixelX, layerAlpha << 24 | RGB(r, g, b));
		}
	}
}

void Canvas::line(int x1, int y1, int x2, int y2, int color) {
	int xDiff = x2 - x1;
	int yDiff = y2 - y1;
	float steps = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
	float xStep = xDiff / steps;
	float yStep = yDiff / steps;
	float x = x1;
	float y = y1;
	for(int i = 0; i < steps; i++) {
		x += xStep;
		y += yStep;
		setPixel((int) y, (int) x, color);
	}
}

void Canvas::rect(int left, int top, int right, int bottom, int color) {
	for(int y = top; y < bottom; y++)
		for(int x = left; x < right; x++) {
			setPixel(y, x, color);
		}
}

void Canvas::roundRect(int left, int top, int right, int bottom, int radius, int color) {
	rect(left + radius, top, right - radius, top + radius, color);
	rect(left, top + radius, right, bottom - radius, color);
	rect(left + radius, bottom - radius, right - radius, bottom, color);
	circle(left + radius, top + radius, radius, color);
	circle(right - radius, top + radius, radius, color);
	circle(left + radius, bottom - radius, radius, color);
	circle(right - radius, bottom - radius, radius, color);
}

void Canvas::circle(int xPos, int yPos, int radius, int color) {
	for(int y = yPos - radius; y < yPos + radius; y++) {
		int sliceWidth = (float) radius * sqrt(1. - pow((yPos - y) / (float) radius, 2));
		//(float) radius * cos(3.14159265 * (y - yPos) / radius) / 2;
		for(int x = xPos - sliceWidth; x < xPos + sliceWidth; x++) {
			setPixel(y, x, color);
		}
	}
}
