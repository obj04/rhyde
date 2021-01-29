#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../UI.hpp"


class WindowEvent {
	public:
	typedef enum {
		WINDOW_CLOSE,
	} Type;
	Type type;
	
	WindowEvent(Type t);
};

class WindowListener {
	public:
	void* object;
	void (*handlers[3])(void*, WindowEvent*);

	WindowListener(void* obj);
	void onEvent(WindowEvent* e);
};

class Window: public GraphicsComponent {
	public:
	char* title;
	GraphicsComponent* closeButton;

	Window(char* title, PSFFont* font);
	void onWindowEvent(WindowEvent* e);
};

#endif
