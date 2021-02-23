#include "ServerEvent.hpp"


ServerEvent::ServerEvent(MouseEvent* e, int windowId) {
	mouse = e;
	targetWindow = windowId;
}

ServerEvent::ServerEvent(Request* r) {
	char* data = r->getObject(0).object;

	mouse = (MouseEvent*) new char[sizeof(MouseEvent)];
	memcpy(mouse, data, sizeof(MouseEvent));
}

void ServerEvent::addTo(Request* r) {
	char mouseData[sizeof(MouseEvent)];
	memcpy(mouseData, mouse, sizeof(MouseEvent));

	char data[sizeof(mouseData)];
	memcpy(data, mouseData, sizeof(MouseEvent));
	r->addObject(data, sizeof(data));
}
