#include "Button.hpp"


Button::Button(API* ptr): Component(ptr) {
	api = ptr;
	label = new Label(api);
	label->setColor(0xff000000);
	
	renderer = [](Component* comp) -> void {
		Button* button = (Button*) comp;
		button->fill(0);
		if(button->hovered) {
			button->roundRect(0, 0, button->width, button->height, 4, 0xff000000);
			button->roundRect(2, 2, button->width - 2, button->height - 2, 4, 0xffffffff);
		} else {
			button->roundRect(0, 0, button->width, button->height, 4, 0xffffffff);
		}
		button->centerLabel();
		button->assimilate(button->label);
	};

	packer = [](Component* comp) -> void {
		Button* button = (Button*) comp;
		button->resize(button->label->width + 8, button->label->height + 8);
	};
	
	eventHandler = [](Component* comp, ServerEvent e) -> void {
		if(e.mouse.type != e.mouse.CLICK)
			return;

		Button* button = (Button*) comp;
		if(button->callback != NULL)
			button->callback(button, button->callbackArgs);
	};
}

Button::Button(API* ptr, char* txt): Button(ptr) {
	setLabel(txt);
}

void Button::setLabel(char* txt) {
	label->setText(txt);
	label->pack();
	label->render();
}

void Button::setCallback(void (*function)(Button*, void*)) {
	callback = function;
}

void Button::setCallbackArguments(void* args) {
	callbackArgs = args;
}

void Button::centerLabel() {
	label->setPosition((width - label->width) / 2, (height - label->height) / 2);
}
