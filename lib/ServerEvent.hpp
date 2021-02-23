#pragma once

#include <cstring>
#include "Request.hpp"
#include "MouseEvent.hpp"


class ServerEvent {
	public:
	char* data;
	MouseEvent* mouse;
	int targetWindow;

	ServerEvent(MouseEvent* e, int windowId);
	ServerEvent(Request* r);
	void addTo(Request* r);
};
