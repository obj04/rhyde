#pragma once

#include "../../../lib/Graphics.hpp"


class ButtonEvent {

};

class ButtonListener {};

class Button: public LayeredCanvas {
	public:
	char* label;
	void (*callback)(void* button);

	Button(char* label, PSFFont* font);
	void onButtonEvent(ButtonEvent* e);
};
