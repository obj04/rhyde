#ifndef MOUSEEVENT
#define MOUSEEVENT

class MouseEvent {
	public:
	int xPos, yPos;
	signed char xDiff, yDiff;
	unsigned char left, middle, right = 0;

	MouseEvent(int x, int y, signed char dx, signed char dy, unsigned char l, unsigned char m, unsigned char r) {
		xPos = x;
		yPos = y;
		xDiff = dx;
		yDiff = - dy;
		left = l;
		middle = m;
		right = r;
	}
};

#endif
