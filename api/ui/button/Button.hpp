#pragma once

#include "../component/Component.hpp"


class ButtonEvent {};

class ButtonListener {};

class Button: public Component {
	public:
	char* label;
	void (*callback)(void* button);

	Button();
	void onButtonEvent(ButtonEvent* e);
};
