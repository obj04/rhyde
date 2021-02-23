#pragma once

#include "../component/Component.hpp"


class Button: public Component {
	public:
	char* label;
	void (*callback)(Button*, void*);
	void* callbackArgs;

	Button();
	void setCallback(void (*function)(Button*, void*));
	void setCallbackArguments(void* args);
};
