#include "ServerEvent.hpp"
#include <linux/input.h>


void ServerEvent::readMouseData(char* data) {
	source = MOUSE;
	mouse.xDiff = data[1];
	mouse.yDiff = - data[2];
	mouse.left = data[0] & 0x01;
	mouse.middle = data[0] & 0x04;
	mouse.right = data[0] & 0x02;
	if(mouse.xDiff == 0 && mouse.yDiff == 0) {
		if(mouse.left == 1) {
			mouse.type = mouse.CLICK;
		}
	} else {
		if(mouse.left == 1)
			mouse.type = mouse.DRAG;
		else
			mouse.type = mouse.MOVE;
	}
}

void ServerEvent::readKeyboardData(char* data) {
	struct input_event evt = *((struct input_event*) data);
	if(evt.type == EV_KEY) {
		source = KEYBOARD;
		switch(evt.value) {
			case 0:		keyboard.type = keyboard.KEYUP;			break;
			case 1:		keyboard.type = keyboard.KEYDOWN;		break;
			case 2:		keyboard.type = keyboard.AUTOREPEAT;	break;
		}
		keyboard.scancode = evt.code;
	}

}
