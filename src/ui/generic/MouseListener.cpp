#include "../UI.hpp"


MouseListener::MouseListener(void* obj) {
	object = obj;
}

void MouseListener::onEvent(MouseEvent* e) {
	if(handlers[e->type] != NULL)
		handlers[e->type](object, e);
}
