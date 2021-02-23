#include "Window.hpp"


Window::Window(API* a): Container() {
	api = a;
	Request* request = new Request();
	request->addObject(Command::WINDOW_CREATE);
	Conversation* conv = api->send(request);
	conv->lock->acquire();
	id = conv->answer->getIntValue(0);
	printf("received id: %d\n", id);
	api->registerComponent(this);
}

void Window::setPosition(int x, int y) {
	xPos = x;
	yPos = y;
	Request* request = new Request();
	request->addObject(Command::WINDOW_REPOSITION);
	request->addObject(id);
	request->addObject(x);
	request->addObject(y);
	api->send(request);
}

void Window::setSize(unsigned int w, unsigned int h) {
	resize(w, h);
	Request* request = new Request();
	request->addObject(Command::WINDOW_RESIZE);
	request->addObject(id);
	request->addObject(w);
	request->addObject(h);
	api->send(request);
}

void Window::setVisible(bool visible) {
	flags = visible ? flags | WindowFlags::SHOWN : flags & ~WindowFlags::SHOWN;
	Request* request = new Request();
	request->addObject(Command::WINDOW_SET_ATTRIBUTES);
	request->addObject(id);
	request->addObject(flags);
	api->send(request);
}

void Window::update() {
	Request* request = new Request();
	request->addObject(Command::WINDOW_UPDATE);
	request->addObject(id);
	request->addObject(bitmap, width * height * 4);
	api->send(request);
}
