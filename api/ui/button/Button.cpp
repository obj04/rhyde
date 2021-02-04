#include "Button.hpp"


Button::Button(char* label, PSFFont* font): LayeredCanvas(font->width * strlen(label) + 8, font->height + 8) {
	this->label = label;
	roundRect(0, 0, width, height, 4, 0xffaaaaaa);
}

void Button::onButtonEvent(ButtonEvent* e) {
	if(callback != NULL)
		callback(this);
}
