#include "Window.hpp"


Window::Window(Client* c) {
	client = c;
	Request* request = new Request();
	request->addObject(Command::WINDOW_CREATE);
	Conversation* conv = client->send(request);
	printf("lock acquire\n");
	conv->lock->acquire();
	id = conv->answer->getIntValue(0);
	printf("received id: %d\n", id);
}

void Window::setPosition(int x, int y) {
	Request* request = new Request();
	request->addObject(Command::WINDOW_REPOSITION);
	request->addObject(id);
	request->addObject(x);
	request->addObject(y);
	client->send(request);
}

void Window::setSize(unsigned int w, unsigned int h) {
	resize(w, h);
	Request* request = new Request();
	request->addObject(Command::WINDOW_RESIZE);
	request->addObject(id);
	request->addObject(w);
	request->addObject(h);
	client->send(request);
}

void Window::setVisible(bool visible) {
	flags = visible ? flags | WindowFlags::SHOWN : flags & ~WindowFlags::SHOWN;
	Request* request = new Request();
	request->addObject(Command::WINDOW_SET_ATTRIBUTES);
	request->addObject(id);
	request->addObject(flags);
	client->send(request);
}

void Window::update() {
	Request* request = new Request();
	request->addObject(Command::WINDOW_UPDATE);
	request->addObject(id);
	request->addObject(bitmap, width * height * 4);
	client->send(request);
}
