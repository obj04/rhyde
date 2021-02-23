#pragma once

#include "../../API.hpp"
#include "../../Conversation.hpp"
#include "../../../lib/Request.hpp"
#include "../container/Container.hpp"


class Window: public Container {
	API* api;
	unsigned int id;
	unsigned int flags;

	public:
	Window(API* c);
	void setPosition(int x, int y);
	void setSize(unsigned int w, unsigned int h);
	void setVisible(bool visible);
	void update();
};
