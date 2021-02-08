#include "Graphics.hpp"


LayeredCanvas::LayeredCanvas(unsigned int w, unsigned int h): LayeredCanvas(0, 0, w, h) {};

LayeredCanvas::LayeredCanvas(int x, int y, unsigned int w, unsigned int h): Canvas(w, h) {
	xPos = x;
	yPos = y;
}

bool LayeredCanvas::contains(int x, int y) {
	if(    x >= this->xPos
		&& x <= this->xPos + this->width
		&& y >= this->yPos
		&& y <= this->yPos + this->height) {
		return true;
	}
	return false;
}
