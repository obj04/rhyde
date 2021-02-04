#include "../lib/Thread.hpp"
#include "time.hpp"
#include "Server.hpp"


DisplayManager::DisplayManager() {
	fb = new Framebuffer();
	layers[0] = new LayeredCanvas(fb->width, fb->height);
	layers[15] = new LayeredCanvas(fb->width / 2, fb->height / 2, 32, 32);

	layers[15]->line(0, 0, 0, 12, 0xff000000);
	layers[15]->line(0, 0, 8, 8, 0xff000000);
	layers[15]->line(8, 8, 0, 12, 0xff000000);
	layers[15]->line(5, 10, 8, 16, 0xff000000);

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
			usleep(1000);
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

				LayeredCanvas* layer;
				for(int i = 1; i < 16; i++) {
					layer = dm->layers[i];
					if(layer != NULL) {
						if(    e->xPos >= layer->xPos
							&& e->xPos <= layer->xPos + layer->width
							&& e->yPos >= layer->yPos
							&& e->yPos <= layer->yPos + layer->height) {
							printf("layer %d clicked\n", i);
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

DisplayManager::~DisplayManager() {
	interrupt();
	autoRefresh->join();
}

void DisplayManager::refresh() {
	fb->flush();
	screen->fill(0);
	for(int z = 0; z < 64; z++) {
		if(layers[z] != NULL) {
			screen->assimilate(layers[z]->xPos, layers[z]->yPos, layers[z]->width, layers[z]->height, layers[z]->bitmap);
		}
	}
	fb->update();
}

void DisplayManager::interrupt() {
	stopRequested = true;
}

bool DisplayManager::interrupted() {
	return stopRequested;
}
