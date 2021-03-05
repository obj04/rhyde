#include "Label.hpp"


Label::Label(API* ptr): Component(ptr) {
	api = ptr;
	renderer = [](Component* c) -> void {
		printf("renderer\n");
		Label* lbl = (Label*) c;
		lbl->fill(0);
		if(lbl->txt == NULL || lbl->font == NULL)
			return;
		lbl->text(0, 0, lbl->font, lbl->txt, lbl->color);
	};
	packer = [](Component* c) -> void {
		Label* label = (Label*) c;
		label->resize(strlen(label->txt) * label->font->width, label->font->height);
	};
	font = api->defaultFont;
}

Label::Label(API* ptr, char* t): Label(ptr) {
	setText(t);
}

void Label::setText(char* t) {
	txt = t;
}

void Label::setFont(PSFFont* f) {
	font = f;
}

void Label::setColor(unsigned int c) {
	color = c;
}
