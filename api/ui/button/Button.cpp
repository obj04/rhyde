#include "Button.hpp"


Button::Button() {
	resize(16, 16);
	roundRect(0, 0, width, height, 4, 0xffaaaaaa);
	eventHandler = [](Component* comp, ServerEvent* e) -> void {
		if(e->mouse->type != MouseEvent::Type::MOUSEDOWN)
			return;

		Button* button = (Button*) comp;
		if(button->callback != NULL)
			button->callback(button, button->callbackArgs);
	};
}

void Button::setCallback(void (*function)(Button*, void*)) {
	callback = function;
}

void Button::setCallbackArguments(void* args) {
	callbackArgs = args;
}
