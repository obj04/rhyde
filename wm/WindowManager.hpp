#pragma once
#include "../../lib/Graphics.hpp"


class Window: public GraphicsComponent {
	public:
	int xPos, yPos;
	char* title;
	Canvas* minimizeButton;
	Canvas* maximizeButton;
	Canvas* closeButton;

	Window(char* title);
};
