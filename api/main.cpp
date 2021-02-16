#include "Client.hpp"
#include "ui/window/Window.hpp"
#include <cmath>


int main() {
	Client* client = new Client("localhost", 38642);
	Window* window = new Window(client);
	window->setPosition(100, 100);
	window->setSize(640, 480);
	window->setVisible(true);
	for(int y = 0; y < window->height; y++) {
		for(int x = 0; x < window->width; x++) {
			window->setPixel(y, x, 0xff000000 | RGB(127, (255 - (255 * x) / window->width), ((255 * y) / window->height)));
		}
		window->update();
	}
	window->update();
	return 0;
}
