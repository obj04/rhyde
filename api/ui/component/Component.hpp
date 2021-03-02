#pragma once

#include "../../API.hpp"
#include "../../../lib/ServerEvent.hpp"
#include "../../../lib/Canvas.hpp"


class Component: public Canvas {
	protected:
	API* api;
	void (*renderer)(Component*);
	void (*packer)(Component*);
	void (*eventHandler)(Component*, ServerEvent);
	
	public:
	Component(API* ptr);
	void render();
	void pack();
	void handleEvent(ServerEvent e);
};