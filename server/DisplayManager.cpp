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

	keyboardListener = new Thread([](void* args) -> void* {
		DisplayManager* dm = (DisplayManager*) args;
		int keyboard = open("/dev/input/event3", O_RDWR);
		char data[24];

		while(!dm->interrupted()) {
			if(read(keyboard, data, sizeof(data)) > 0) {
				ServerEvent e;
				e.mouse.xPos = dm->mousePointer->xPos;
				e.mouse.yPos = dm->mousePointer->yPos;
				e.readKeyboardData(data);
				dm->eventQueue->push(&e);
			}
			usleep(10000);
		}
		close(keyboard);
		return NULL;
	}, (void*) this);
	keyboardListener->start();

	mouseListener = new Thread([](void* args) -> void* {
		DisplayManager* dm = (DisplayManager*) args;
		int mouse = open("/dev/input/mice", O_RDWR);
		char data[3];
		
		while(!dm->interrupted()) {
			if(read(mouse, data, sizeof(data)) > 0) {
				ServerEvent e;
				e.mouse.xPos = dm->mousePointer->xPos;
				e.mouse.yPos = dm->mousePointer->yPos;
				e.readMouseData(data);
				e.mouse.xDiff = dm->getAcceleratedMouseMovementDistance(e.mouse.xDiff);
				e.mouse.yDiff = dm->getAcceleratedMouseMovementDistance(e.mouse.yDiff);
				dm->mousePointer->xPos += e.mouse.xDiff;
				dm->mousePointer->yPos += e.mouse.yDiff;

				Canvas* layer;
				for(int i = 1; i < 16; i++) {
					layer = dm->layers[i];
					if(layer != NULL) {
						if(layer->contains(e.mouse.xPos, e.mouse.yPos)) {
							dm->eventQueue->push(&e);
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

int DisplayManager::getAcceleratedMouseMovementDistance(int input) {
	int sign = input / abs(input);
	int val = abs(input);
	return sign * val * ((val / 4) + 1);
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
