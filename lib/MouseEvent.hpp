#pragma once


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