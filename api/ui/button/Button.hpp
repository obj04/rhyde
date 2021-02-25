#pragma once

#include "../component/Component.hpp"
#include "../label/Label.hpp"


class Button: public Component {
	Label* label;
	void (*callback)(Button*, void*);
	void* callbackArgs;
	
	public:
	Button(API* ptr);
	Button(API* ptr, char* txt);
	void setLabel(char* txt);
	void setCallback(void (*function)(Button*, void*));
	void setCallbackArguments(void* args);
	void centerLabel();
};
