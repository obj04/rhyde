#include "../UI.hpp"


Canvas::Canvas(int w, int h) {
	width = w;
	height = h;
	bitmap = new int*[height];
	for(int i = 0; i < height; i++) {
		bitmap[i] = new int[width];
	}
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
					bitmap[yPos + y][xPos + i * font->width + x] = fg;
				else
					bitmap[yPos + y][xPos + i * font->width + x] = bg;
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
		bitmap[(int) y][(int) x] = color;
	}
}

void Canvas::rect(int left, int top, int right, int bottom, int color) {
	for(int y = top; y < bottom; y++)
		for(int x = left; x < right; x++) {
			bitmap[y][x] = color;
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
			bitmap[y][x] = color;
		}
	}
}
