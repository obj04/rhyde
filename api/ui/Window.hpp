#pragma once

#include "../API.hpp"
#include "../Conversation.hpp"
#include "../../lib/Request.hpp"
#include "Container.hpp"


class Window: public Container {
	API* api;
	unsigned int flags;

	public:
	Window(API* ptr);
	void setPosition(int x, int y);
	void setSize(unsigned int w, unsigned int h);
	void setVisible(bool visible);
	void update();
};
