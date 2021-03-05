#include "API.hpp"
#include "ui/Window.hpp"
#include "ui/Button.hpp"
#include <cmath>


int main() {
	API* api = new API();
	api->connect("localhost", 38642);
	Window* window = new Window(api);
	window->setPosition(100, 100);
	window->setSize(640, 480);
	window->setVisible(true);
	for(int y = 0; y < window->height; y++) {
		for(int x = 0; x < window->width; x++) {
			window->setPixel(y, x, 0xff000000 | RGB(127, (255 - (255 * x) / window->width), ((255 * y) / window->height)));
		}
	}
	Button* btn = new Button(api, "move window");
	btn->setPosition(100, 100);
	btn->setCallback([](Button* button, void* args) -> void {
		int x = rand() % 1920;
		int y = rand() % 1080;
		((Window*) args)->setPosition(x, y);
	});
	btn->setCallbackArguments(window);
	btn->pack();
	window->add(btn);
	window->render();
	window->update();
	while(true) {
		sleep(1);
	}
	return 0;
}
