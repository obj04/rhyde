#include "../../rhyde/RhyDE.hpp"
#include "Window.hpp"


Window::Window(char* title, PSFFont* font): GraphicsComponent(100, 100, 640, 480) {
	this->title = title;
	fill(0);
	layers[0] = new GraphicsComponent(0, 0, width, height);
	layers[0]->roundRect(0, 0, width, height, 10, 0x80ffffff);
	layers[1] = new GraphicsComponent(8, 8, width - 16, 32);
	layers[1]->text(0, 0, font, title, 0xff000000);
	minimizeButton = new GraphicsComponent(width - 120 + 0, 8, 32, 32);
	minimizeButton->roundRect(0, 0, 32, 32, 4, 0xffaaaaaa);
	layers[2] = minimizeButton;
	maximizeButton = new GraphicsComponent(width - 120 + 40, 8, 32, 32);
	maximizeButton->roundRect(0, 0, 32, 32, 4, 0xffaaaaaa);
	layers[3] = maximizeButton;
	closeButton = new GraphicsComponent(width - 120 + 80, 8, 32, 32);
	closeButton->roundRect(0, 0, 32, 32, 4, 0xffff0000);
	layers[4] = closeButton;
	layers[5] = new GraphicsComponent(8, 48, width - 16, height - 56);
	layers[5]->fill(0xffffffff);
	
	mouseListener->handlers[MouseEvent::Type::MOUSEDOWN] = [](void* source, MouseEvent* e) -> void {
		Window* comp = (Window*) source;
		comp->passEvent(source, e);
		/*GraphicsComponent* layer = comp->closeButton;
		e->xPos -= comp->xPos;
		e->yPos -= comp->yPos;
		printf("window handler\n");
		if(layer != NULL) {
			if(layer->contains(e->xPos, e->yPos)) {
				//comp->xPos = 0;
				//WindowEvent* evt = new WindowEvent(WindowEvent::Type::WINDOW_CLOSE);
				//comp->onWindowEvent(evt);
				//layer->onMouseEvent(e);
			}
		}*/
	};
}

GraphicsComponent* Window::getContainer() {
	return layers[5];
}

void Window::onWindowEvent(WindowEvent* e) {
	return;
}
