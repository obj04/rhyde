#include "RhyDE.hpp"


WindowManager::WindowManager(int w, int h): GraphicsComponent(w, h) {
	renderer = [](GraphicsComponent* comp) -> void {
		comp->fill(0);
		comp->mergeLayers();
	};
	mouseListener = new MouseListener(this);
	mouseListener->handlers[MouseEvent::Type::MOUSEDRAG] = [](void* source, MouseEvent* e) -> void {
		WindowManager* wm = (WindowManager*) source;
		Window* layer;
		for(int i = 0; i < 16; i++) {
			layer = (Window*) wm->layers[i];
			if(layer != NULL) {
				if(    e->xPos >= layer->xPos
					&& e->xPos <= layer->xPos + layer->width
					&& e->yPos >= layer->yPos
					&& e->yPos <= layer->yPos + layer->height) {
					//WindowEvent* evt = new WindowEvent(WindowEvent::Type::WINDOW_CLOSE);
					//comp->onWindowEvent(evt);
					//layer->onMouseEvent(e);
					layer->xPos += e->xDiff;
					layer->yPos += e->yDiff;
				}
			}
		}
	};
}

void WindowManager::closeWindow(int index) {
	delete layers[index];
	layers[index] = NULL;
}
