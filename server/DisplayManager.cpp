#include "../lib/Thread.hpp"
#include "../lib/Clock.hpp"
#include "Server.hpp"


DisplayManager::DisplayManager() {
	eventQueue = new Queue();
	fb = new Framebuffer();
	screen = new Canvas(fb->width, fb->height);
	screen->bitmap = fb->bitmap;
	layers[0] = new Window();
	layers[0]->xPos = 0;
	layers[0]->yPos = 0;
	layers[0]->resize(fb->width, fb->height);
	layers[0]->flags = WindowFlags::SHOWN;
	mousePointer = new Canvas(fb->width / 2, fb->height / 2, 32, 32);
	int pointerColor = 0xff000000;
	mousePointer->line(0, 0, 0, 12, pointerColor);
	mousePointer->line(0, 0, 8, 8, pointerColor);
	mousePointer->line(8, 8, 0, 12, pointerColor);
	mousePointer->line(5, 10, 8, 16, pointerColor);
	
	autoRefresh = new Thread([](void* args) -> void* {
		DisplayManager* dm = (DisplayManager*) args;
		int frame = 0;
		long t = Clock::getMillis();
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
					dm->mousePointer->xPos, dm->mousePointer->yPos,
					data[1], data[2], 
					data[0] & 0x01, data[0] & 0x04, data[0] & 0x02);
				dm->mousePointer->xPos += e->xDiff;
				dm->mousePointer->yPos += e->yDiff;

				Canvas* layer;
				for(int i = 1; i < 16; i++) {
					layer = dm->layers[i];
					if(layer != NULL) {
						if(    e->xPos >= layer->xPos
							&& e->xPos <= layer->xPos + layer->width
							&& e->yPos >= layer->yPos
							&& e->yPos <= layer->yPos + layer->height) {
							dm->eventQueue->push(new ServerEvent(e, i));
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
	for(int z = 0; z < 64; z++) {
		if(layers[z] != NULL) {
			if(layers[z]->flags & WindowFlags::SHOWN) {
				layers[z]->lock->acquire();
				screen->assimilate(layers[z]->xPos, layers[z]->yPos, layers[z]->width, layers[z]->height, layers[z]->bitmap);
				layers[z]->lock->release();
			}
		}
	}
	screen->assimilate(mousePointer->xPos, mousePointer->yPos, mousePointer->width, mousePointer->height, mousePointer->bitmap);
	fb->update();
	usleep(10000);
}

void DisplayManager::interrupt() {
	stopRequested = true;
}

bool DisplayManager::interrupted() {
	return stopRequested;
}

unsigned int DisplayManager::createWindow() {
	for(int i = 0; i < 64; i++) {
		if(layers[i] == NULL) {
			layers[i] = new Window();
			layers[i]->id = i;
			return i;
		}
	}
	return -1;
}

Window* DisplayManager::getWindow(unsigned int id) {
	return layers[id];
}

void DisplayManager::destroyWindow(unsigned int id) {
	delete layers[id];
	layers[id] = NULL;
}
