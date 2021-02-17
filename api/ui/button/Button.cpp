#include "Button.hpp"


Button::Button() {
	resize(16, 16);
	roundRect(0, 0, width, height, 4, 0xffaaaaaa);
}

void Button::onButtonEvent(ButtonEvent* e) {
	if(callback != NULL)
		callback(this);
}
