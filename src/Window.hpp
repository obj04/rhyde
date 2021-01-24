#ifndef WINDOW
#define WINDOW

#include "GraphicsComponent.hpp"


class Window: public GraphicsComponent {
	public:
	char* title;

	Window(char* title): GraphicsComponent(100, 100, 640, 480) {
		this->title = title;
		fill(0);
		layers[0] = new GraphicsComponent(0, 0, width, height);
		layers[0]->roundRect(0, 0, width, height, 10, 0x80ffffff);
		layers[1] = new GraphicsComponent(8, 8, width - 16, 32);
		layers[1]->text(0, 0, largeFont, title, 0xff000000);
		this->render();
	}

	void onDrag(MouseEvent* e) {
		xPos += e->xDiff;
		yPos += e->yDiff;
	}
};

#endif
