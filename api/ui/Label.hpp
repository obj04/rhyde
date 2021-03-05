#pragma once

#include "Component.hpp"


class Label: public Component {
	PSFFont* font;
	char* txt;
	unsigned int color;

	public:
	Label(API* ptr);
	Label(API* ptr, char* t);
	void setText(char* t);
	void setFont(PSFFont* f);
	void setColor(unsigned int c);
};
