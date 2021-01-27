#ifndef WINDOWEVENT
#define WINDOWEVENT

class WindowEvent {
	public:
	typedef enum {
		WINDOW_CLOSE,
	} Type;

	Type type;

	WindowEvent(Type t) {
		type = t;
	}
};

#endif
