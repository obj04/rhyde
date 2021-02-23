#include "MouseEvent.hpp"


MouseEvent::MouseEvent(int x, int y, signed char dx, signed char dy, unsigned char l, unsigned char m, unsigned char r) {
	xPos = x;
	yPos = y;
	xDiff = dx;
	yDiff = - dy;
	left = l;
	middle = m;
	right = r;
	type = Type::NOTHING;
	if(xDiff == 0 && yDiff == 0) {
		if(left == 1) {
			type = Type::MOUSEDOWN;
		}
	} else {
		if(left == 1)
			type = Type::MOUSEDRAG;
		else
			type = Type::MOUSEMOVE;
	}
}
