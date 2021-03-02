#pragma once

#include <cstring>
#include "Request.hpp"


class ServerEvent {
	public:
	enum {
		MOUSE,
		KEYBOARD,
	} source;
	struct {
		unsigned short scancode;
		enum {
			KEYDOWN,
			KEYUP,
			AUTOREPEAT,
		} type;
	} keyboard;
	struct {
		int xPos, yPos;
		signed char xDiff, yDiff;
		unsigned char left, middle, right = 0;
		enum {
			CLICK,
			DRAG,
			MOVE,
		} type;
	} mouse;

	void readMouseData(char* data);
	void readKeyboardData(char* data);
};
