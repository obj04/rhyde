#include "Window.hpp"


WindowListener::WindowListener(void* obj) {
	object = obj;
}

void WindowListener::onEvent(WindowEvent* e) {
	if(handlers[e->type] != NULL)
		handlers[e->type](object, e);
}
