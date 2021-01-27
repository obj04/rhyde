#ifndef WINDOW
#define WINDOW

#include <ui/Canvas.hpp>
#include "GraphicsComponent.hpp"
#include "event/MouseEvent.hpp"
#include "event/WindowEvent.hpp"

class Window: public GraphicsComponent {
	public:
	char* title;
	GraphicsComponent* closeButton;

	Window(char* title): GraphicsComponent(100, 100, 640, 480) {
		this->title = title;
		fill(0);
		layers[0] = new GraphicsComponent(0, 0, width, height);
		layers[0]->roundRect(0, 0, width, height, 10, 0x80ffffff);
		layers[1] = new GraphicsComponent(8, 8, width - 16, 32);
		layers[1]->text(0, 0, largeFont, title, 0xff000000);
		layers[2] = new GraphicsComponent(8, 48, width - 16, height - 56);
		layers[2]->fill(0xffffffff);
		layers[3] = new GraphicsComponent(width - 120, 8, 120, 32);
		layers[3]->roundRect(0, 0, 32, 32, 4, 0xffaaaaaa);
		layers[3]->roundRect(40, 0, 72, 32, 4, 0xffaaaaaa);
		closeButton = new GraphicsComponent(width - 120 + 80, 8, 32, 32);
		closeButton->roundRect(0, 0, 32, 32, 4, 0xffff0000);
		layers[4] = closeButton;

		mouseListener->handlers[MouseEvent::Type::MOUSEDRAG] = [](void* source, MouseEvent* e) -> void {
			Window* comp = (Window*) source;
			GraphicsComponent* layer = comp->layers[2];
			e->xPos -= comp->xPos;
			e->yPos -= comp->yPos;
			if(layer != NULL) {
				if(    e->xPos >= layer->xPos
					&& e->xPos <= layer->xPos + layer->width
					&& e->yPos >= layer->yPos
					&& e->yPos <= layer->yPos + layer->height) {
					layer->onMouseEvent(e);
				} else {
					if(e->type == MouseEvent::Type::MOUSEDRAG) {
						comp->xPos += e->xDiff;
						comp->yPos += e->yDiff;
					}
				}
			}
		};

		mouseListener->handlers[MouseEvent::Type::MOUSEDOWN] = [](void* source, MouseEvent* e) -> void {
			Window* comp = (Window*) source;
			GraphicsComponent* layer = comp->layers[4];
			e->xPos -= comp->xPos;
			e->yPos -= comp->yPos;
			if(layer != NULL) {
				if(    e->xPos >= layer->xPos
					&& e->xPos <= layer->xPos + layer->width
					&& e->yPos >= layer->yPos
					&& e->yPos <= layer->yPos + layer->height) {
					comp->xPos = 0;
					WindowEvent* evt = new WindowEvent(WindowEvent::Type::WINDOW_CLOSE);
					comp->onWindowEvent(evt);
					//layer->onMouseEvent(e);
				} else {
					if(e->type == MouseEvent::Type::MOUSEDRAG) {
						comp->xPos += e->xDiff;
						comp->yPos += e->yDiff;
					}
				}
			}
		};
	}

	void onWindowEvent(WindowEvent* e) {
            if(e->type == WindowEvent::Type::WINDOW_CLOSE)
                delete this;
	};
};

#endif
