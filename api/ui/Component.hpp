#pragma once

#include "../API.hpp"
#include "../../lib/ServerEvent.hpp"
#include "../../lib/Point.hpp"
#include "../../lib/Canvas.hpp"


class Component: public Canvas {
	protected:
	void (*renderer)(Component*);
	void (*packer)(Component*);
	void (*eventHandler)(Component*, ServerEvent);
	
	public:
	API* api;
	unsigned int id;
	Component* parent;
	bool hovered = false;
	bool focused = false;

	Component(API* ptr);
	void render();
	void pack();
	void handleEvent(ServerEvent e);
	Point getAbsolutePosition();
};