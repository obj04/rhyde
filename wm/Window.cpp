#include "../../lib/Graphics.hpp"
#include "WindowManager.hpp"


Window::Window(char* title): GraphicsComponent(100, 100, 640, 480) {
	this->title = title;
}
