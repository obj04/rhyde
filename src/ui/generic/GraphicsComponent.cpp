#include "../UI.hpp"


GraphicsComponent::GraphicsComponent(int w, int h): GraphicsComponent(0, 0, w, h) {};

GraphicsComponent::GraphicsComponent(int x, int y, int w, int h): Canvas(w, h) {
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	bitmap = new int*[height];
	for(int i = 0; i < height; i++) {
		bitmap[i] = new int[width];
	}

	mouseListener = new MouseListener(this);
	mouseListener->handlers[MouseEvent::Type::MOUSEDOWN] = [](void* source, MouseEvent* e) -> void {
		GraphicsComponent* comp = (GraphicsComponent*) source;
		for(GraphicsComponent* layer : comp->layers) {
			if(layer != NULL) {
				if(    e->xPos >= layer->xPos
					&& e->xPos <= layer->xPos + layer->width
					&& e->yPos >= layer->yPos
					&& e->yPos <= layer->yPos + layer->height) {
					layer->onMouseEvent(e);
				}
			}
		}
	};
	renderer = [](GraphicsComponent* comp) -> void {
		comp->mergeLayers();
	};
}

void GraphicsComponent::render() {
	renderer(this);
}

void GraphicsComponent::onMouseEvent(MouseEvent* e) {
	if(mouseListener != NULL)
		mouseListener->onEvent(e);
}

void GraphicsComponent::mergeLayers() {
	bool toDo[16];
	for(int i = 0; i < 16; i++) {
		toDo[i] = layers[i] != NULL;
	}
	
	unsigned int pixelX, pixelY, color, layerColor, newColor;
	unsigned char r, g, b, aLayer, aBackground;
	while([&]() -> bool {
		int left = 0;
		for(int i = 0; i < 16; i++)
			if(toDo[i])
				left++;
		return left != 0;
	}()) {
		int pos = -1;
		for(int i = 0; i < 16; i++)
			if(toDo[i]) {
				if(pos == -1)
					pos = i;
				else if(layers[i]->zPos < layers[pos]->zPos)
					pos = i;
			}
		toDo[pos] = false;
		
		layers[pos]->render();
		for(int y = 0; y < layers[pos]->height; y++) {
			for(int x = 0; x < layers[pos]->width; x++) {
				pixelX = layers[pos]->xPos + x;
				pixelY = layers[pos]->yPos + y;
				color = bitmap[pixelY][pixelX];
				layerColor = layers[pos]->bitmap[y][x];
				aLayer = layerColor >> 24 % 256;
				aBackground = (color >> 24 % 256);
				if(aLayer == 0)
					continue;
				r = (((color >> 16) % 256) * aBackground + ((layerColor >> 16) % 256) * aLayer) / (aLayer + aBackground);
				g = (((color >> 8) % 256) * aBackground + ((layerColor >> 8) % 256) * aLayer) / (aLayer + aBackground);
				b = ((color % 256) * aBackground + (layerColor % 256) * aLayer) / (aLayer + aBackground);
				bitmap[pixelY][pixelX] =  aLayer << 24 | RGB(r, g, b);
			}
		}
	}
}
