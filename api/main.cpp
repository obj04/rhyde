#include "Client.hpp"
#include <cmath>
#include "../server/time.hpp"


int main() {
	Client* client = new Client("localhost", 38642);
	unsigned int windowId = client->createWindow();
	client->setWindowPosition(windowId, 200, 200);
	client->resizeWindow(windowId, 640, 480);
	client->setWindowAttributes(windowId, WindowAttributes::SHOWN);
	Canvas* canvas = new Canvas(640, 480);
	for(int y = 0; y < canvas->height; y++) {
		for(int x = 0; x < canvas->width; x++) {
			canvas->setPixel(y, x, 0xff << 24 | RGB(127, (255 - (255 * x) / canvas->width), ((255 * y) / canvas->height)));
		}
	}
	client->updateWindow(windowId, canvas);
	return 0;
}
