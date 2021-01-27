#ifndef MOUSELISTENER
#define MOUSELISTENER

#include <cstdlib>
#include <event/MouseEvent.hpp>

class MouseListener {
	public:
	void* object;
	void (*handlers[3])(void*, MouseEvent*);

	MouseListener(void* obj) {
		object = obj;
	}

	void onEvent(MouseEvent* e) {
		if(handlers[e->type] != NULL)
			handlers[e->type](object, e);
	}
};

#endif
