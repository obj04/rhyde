#pragma once

#include "../../../lib/ServerEvent.hpp"
#include "../../../lib/Graphics.hpp"


class Component: public Canvas {
	protected:
	void (*renderer)(Component*);
	void (*eventHandler)(Component*, ServerEvent*);
	
	public:
	void render();
	void handleEvent(ServerEvent* e);
};