#ifndef WINDOWLISTENER
#define WINDOWLISTENER

#include <cstdlib>
#include <event/WindowEvent.hpp>

class WindowListener {
	public:
	void* object;
	void (*handlers[3])(void*, WindowEvent*);

	WindowListener(void* obj) {
		object = obj;
	}

	void onEvent(WindowEvent* e) {
		if(handlers[e->type] != NULL)
			handlers[e->type](object, e);
	}
};

#endif
