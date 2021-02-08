#include "Client.hpp"


int main() {
	Client* client = new Client("localhost", 38642);
	unsigned int windowId = client->createWindow();
	client->resizeWindow(windowId, 100, 100, 640, 480);
	client->setWindowAttributes(windowId, WindowAttributes::SHOWN);
	return 0;
}
