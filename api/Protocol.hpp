#pragma once

enum Command {
	ACK,
	WINDOW_CREATE,
	WINDOW_REPOSITION,
	WINDOW_RESIZE,
	WINDOW_SET_ATTRIBUTES,
	WINDOW_UPDATE,
	WINDOW_DESTROY,
};

enum WindowAttributes {
	XPOS,
	YPOS,
	WIDTH,
	HEIGHT,
	FLAGS,
};

namespace WindowFlags {
	const int SHOWN = 1;
	const int FULLSCREEN = 2;
	const int WM = 4;
};
