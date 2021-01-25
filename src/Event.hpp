#ifndef EVENT
#define EVENT

class Event {
	public:
	typedef enum {
		MOUSEDOWN,
		MOUSEDRAG,
		MOUSEMOVE
	} Type;

	int xPos, yPos;
	signed char xDiff, yDiff;
	unsigned char left, middle, right = 0;
	Type type;
	
	Event(int x, int y, signed char dx, signed char dy, unsigned char l, unsigned char m, unsigned char r) {
		xPos = x;
		yPos = y;
		xDiff = dx;
		yDiff = - dy;
		left = l;
		middle = m;
		right = r;
		if(left == 1) {
			if(xDiff == 0 && yDiff == 0)
				type = Type::MOUSEDOWN;
			if(xDiff != 0 || yDiff != 0) {
				type = Type::MOUSEDRAG;
			}
		} else {
			type = Type::MOUSEMOVE;
		}
	}
};

#endif
