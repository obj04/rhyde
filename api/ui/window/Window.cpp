#include "Window.hpp"


Window::Window(Client* c) {
	client = c;
	Request* request = new Request();
	request->addObject(Command::WINDOW_CREATE);
	request->send(client->fd);
	usleep(1000000);
	id = Request(client->fd).getIntValue(0);
	printf("received id: %d\n", id);
}

void Window::setPosition(int x, int y) {
	Request* request = new Request();
	request->addObject(Command::WINDOW_REPOSITION);
	request->addObject(id);
	request->addObject(x);
	request->addObject(y);
	request->send(client->fd);
}

void Window::setSize(unsigned int w, unsigned int h) {
	resize(w, h);
	Request* request = new Request();
	request->addObject(Command::WINDOW_RESIZE);
	request->addObject(id);
	request->addObject(w);
	request->addObject(h);
	request->send(client->fd);
}

void Window::setVisible(bool visible) {
	flags = visible ? flags | WindowFlags::SHOWN : flags & ~WindowFlags::SHOWN;
	Request* request = new Request();
	request->addObject(Command::WINDOW_SET_ATTRIBUTES);
	request->addObject(id);
	request->addObject(flags);
	request->send(client->fd);
}

void Window::update() {
	Request* request = new Request();
	request->addObject(Command::WINDOW_UPDATE);
	request->addObject(id);
	request->addObject(bitmap, width * height * 4);
	request->send(client->fd);
}
