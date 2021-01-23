#include <cstdio>
#include <cmath>
#include <sys/stat.h>
#include "PSFFont.hpp"
#include "Canvas.hpp"

class NestableCanvas: public Canvas {
	public:
	int xPos;
	int yPos;
	int zPos;
	NestableCanvas* layers[16];

	NestableCanvas(int w, int h): NestableCanvas(0, 0, w, h) {};
	
	NestableCanvas(int x, int y, int w, int h): Canvas(w, h) {
		xPos = x;
		yPos = y;
		width = w;
		height = h;
		bitmap = new int*[height];
		for(int i = 0; i < height; i++) {
			bitmap[i] = new int[width];
		}
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
					bitmap[pixelY][pixelX] = RGB(r, g, b);
				}
			}
		}
	}
};
