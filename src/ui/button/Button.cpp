#include "Button.hpp"


Button::Button(char* label, PSFFont* font): GraphicsComponent(font->width * strlen(label) + 8, font->height + 8) {
	this->label = label;
	roundRect(0, 0, width, height, 4, 0xffaaaaaa);
	layers[0] = new GraphicsComponent(4, 4, font->width * strlen(label), font->height);
	layers[0]->text(0, 0, font, this->label, 0xff000000);
	mouseListener->handlers[MouseEvent::Type::MOUSEDOWN] = [](void* source, MouseEvent* e) -> void {
		((Button*) source)->onButtonEvent(new ButtonEvent());
	};
}

void Button::onButtonEvent(ButtonEvent* e) {
	if(callback != NULL)
		callback(this);
}
