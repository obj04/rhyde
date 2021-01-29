#include "RhyDE.hpp"


WindowManager::WindowManager(int w, int h): GraphicsComponent(w, h) {
	renderer = [](GraphicsComponent* comp) -> void {
		comp->fill(0);
		comp->mergeLayers();
	};
	mouseListener = new MouseListener(this);
	mouseListener->handlers[MouseEvent::Type::MOUSEDRAG] = [](void* source, MouseEvent* e) -> void {
		WindowManager* wm = (WindowManager*) source;
		Window* window;
		for(int i = 0; i < 16; i++) {
			window = (Window*) wm->layers[i];
			if(window != NULL) {
				if(    window->contains(e->xPos, e->yPos)
					&& !window->getContainer()->contains(e->xPos - window->xPos, e->yPos - window->yPos)) {
					window->xPos += e->xDiff;
					window->yPos += e->yDiff;
				}
			}
		}
	};

	mouseListener->handlers[MouseEvent::Type::MOUSEDOWN] = [](void* source, MouseEvent* e) -> void {
		WindowManager* wm = (WindowManager*) source;
		wm->passEvent(source, e);
		Window* window;
		for(int i = 0; i < 16; i++) {
			window = (Window*) wm->layers[i];
			if(window != NULL) {
				if(window->closeButton->contains(e->xPos - window->xPos, e->yPos - window->yPos)) {
					WindowEvent* evt = new WindowEvent(WindowEvent::Type::WINDOW_CLOSE);
					window->onWindowEvent(evt);
					//delete wm->layers[i];
					//printf("wm handler\n");
					wm->layers[i] = NULL;
				}
			}
		}
	};
}

void WindowManager::addWindow(Window* window) {
	int i = 0;
	while(layers[i] != NULL)
		i++;
	layers[i] = window;
}

void WindowManager::closeWindow(int index) {
	delete layers[index];
	layers[index] = NULL;
}
