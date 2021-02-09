#include "Client.hpp"
#include <cmath>
#include "../server/time.hpp"


int main() {
	Client* client = new Client("localhost", 38642);
	unsigned int windowId = client->createWindow();
	client->resizeWindow(windowId, 100, 100, 640, 480);
	client->setWindowAttributes(windowId, WindowAttributes::SHOWN);
	while(true) {
		client->resizeWindow(windowId, 640 + 300 * sin((double) currentTime::millis() / (double) 200.), 100, 640, 480);
		usleep(10000);
	}
	return 0;
}
