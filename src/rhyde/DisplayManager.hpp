#include "../Thread.hpp"
#include "../time.hpp"
#include "Framebuffer.hpp"
#include "../ui/window/Window.hpp"


class DisplayManager {
	private:
	Thread* autoRefresh;
	Thread* mouseListener;
	bool stopRequested = false;

	public:
	GraphicsComponent* layers[64];
	Framebuffer* fb;

	DisplayManager() {
		fb = new Framebuffer();
		layers[0] = new GraphicsComponent(fb->width, fb->height);
		layers[15] = new GraphicsComponent(960, 640, 32, 32);

		autoRefresh = new Thread([](void* args) -> void* {
			DisplayManager* dm = (DisplayManager*) args;
			int frame = 0;
			long t = currentTime::millis();
			while(!dm->interrupted()) {
				dm->refresh();
				/*frame++;
				if((currentTime::millis() - t) >= 1000) {
					printf("%f fps\n", ((float) 1000 * frame) / ((float) currentTime::millis() - t));
					t = currentTime::millis();
					frame = 0;
				}*/
			}
			return NULL;
		}, (void*) this);
		autoRefresh->start();

		mouseListener = new Thread([](void* args) -> void* {
			DisplayManager* dm = (DisplayManager*) args;
			int mouse = open("/dev/input/mice", O_RDWR);
			unsigned char data[3];
			int left, middle, right;
			signed char x, y;

			while(!dm->interrupted()) {
				if(read(mouse, data, sizeof(data)) > 0) {
					MouseEvent* e = new MouseEvent(
						dm->layers[15]->xPos, dm->layers[15]->yPos,
						data[1], data[2], 
						data[0] & 0x01, data[0] & 0x04, data[0] & 0x02);
					dm->layers[15]->xPos += e->xDiff;
					dm->layers[15]->yPos += e->yDiff;

					GraphicsComponent* layer;
					for(int i = 1; i < 16; i++) {
						layer = dm->layers[i];
						if(layer != NULL) {
							if(    e->xPos >= layer->xPos
								&& e->xPos <= layer->xPos + layer->width
								&& e->yPos >= layer->yPos
								&& e->yPos <= layer->yPos + layer->height) {
								layer->onMouseEvent(e);
							}
						}
					}
				}
				usleep(10000);
			}
			close(mouse);
			return NULL;
		}, (void*) this);
		mouseListener->start();
	}

	~DisplayManager() {
		interrupt();
		autoRefresh->join();
	}

	void refresh() {
		unsigned int pixelX, pixelY, screenColor, layerColor, newColor;
		unsigned char r, g, b, a;
		fb->flush();
		for(int z = 0; z < 64; z++) {
			if(layers[z] != NULL) {
				layers[z]->render();
				for(int y = 0; y < layers[z]->height; y++) {
					for(int x = 0; x < layers[z]->width; x++) {
						pixelX = layers[z]->xPos + x;
						pixelY = layers[z]->yPos + y;
						screenColor = fb->bitmap[pixelY][pixelX];
						layerColor = layers[z]->bitmap[y][x];
						a = layerColor >> 24 % 256;
						if(a == 0)
							continue;
						r = (((screenColor >> 16) % 256) * (255 - a) + ((layerColor >> 16) % 256) * a) / 255;
						g = (((screenColor >> 8) % 256) * (255 - a) + ((layerColor >> 8) % 256) * a) / 255;
						b = ((screenColor % 256) * (255 - a) + (layerColor % 256) * a) / 255;
						fb->bitmap[pixelY][pixelX] = a << 24 | RGB(r, g, b);
					}
				}
			}
		}
		fb->update();
	}

	void interrupt() {
		stopRequested = true;
	}

	bool interrupted() {
		return stopRequested;
	}
};
