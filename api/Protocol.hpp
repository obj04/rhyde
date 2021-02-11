enum Request {
	ACK,
	WINDOW_CREATE,
	WINDOW_REPOSITION,
	WINDOW_RESIZE,
	WINDOW_SET_ATTRIBUTES,
	WINDOW_UPDATE,
	WINDOW_DESTROY,
};

namespace WindowAttributes {
	const int SHOWN = 1;
	const int FULLSCREEN = 2;
	const int WM = 4;
};
