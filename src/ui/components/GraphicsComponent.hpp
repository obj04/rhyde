#ifndef GRAPHICSCOMPONENT
#define GRAPHICSCOMPONENT

#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
#include <sys/stat.h>
#include <ui/Canvas.hpp>
#include <event/MouseEvent.hpp>
#include <event/MouseListener.hpp>

#define RGB(r,g,b) b|(g<<8)|(r<<16)

class GraphicsComponent: public Canvas {
	public:
	int xPos;
	int yPos;
	int zPos;
	GraphicsComponent* layers[16];
	MouseListener* mouseListener;

	GraphicsComponent(int w, int h): GraphicsComponent(0, 0, w, h) {};
	
	GraphicsComponent(int x, int y, int w, int h): Canvas(w, h) {
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
	}
	
	void onMouseEvent(MouseEvent* e) {
		if(mouseListener != NULL)
			mouseListener->onEvent(e);
	}

	void render() {
		bool toDo[16];
		for(int i = 0; i < 16; i++) {
			toDo[i] = layers[i] != NULL;
		}
		
		unsigned int pixelX, pixelY, color, layerColor, newColor;
		unsigned char r, g, b, a;
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
					a = layerColor >> 24 % 256;
					if(a == 0)
						continue;
					r = (((color >> 16) % 256) * (255 - a) + ((layerColor >> 16) % 256) * a) / 255;
					g = (((color >> 8) % 256) * (255 - a) + ((layerColor >> 8) % 256) * a) / 255;
					b = ((color % 256) * (255 - a) + (layerColor % 256) * a) / 255;
					bitmap[pixelY][pixelX] =  a << 24 | RGB(r, g, b);
				}
			}
		}
	}
};

#endif
