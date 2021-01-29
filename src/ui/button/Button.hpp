#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../UI.hpp"


class ButtonEvent {

};

class ButtonListener {};

class Button: public GraphicsComponent {
	public:
	char* label;
	void (*callback)(void* button);

	Button(char* label, PSFFont* font);
	void onButtonEvent(ButtonEvent* e);
};

#endif
