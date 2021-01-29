#ifndef RHYDE_HPP
#define RHYDE_HPP

#include "../ui/UI.hpp"
#include "../ui/window/Window.hpp"


class RhyDE {
	public:
	static PSFFont* windowTitleFont;
	static PSFFont* font;
};

class WindowManager: public GraphicsComponent {
	public:

	WindowManager(int w, int h);
	void closeWindow(int index);
};

#endif