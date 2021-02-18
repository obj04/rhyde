#pragma once

#include "../../Client.hpp"
#include "../../Conversation.hpp"
#include "../../../lib/Request.hpp"
#include "../container/Container.hpp"


class Window: public Container {
	Client* client;
	unsigned int id;
	unsigned int flags;

	public:
	Window(Client* c);
	void setPosition(int x, int y);
	void setSize(unsigned int w, unsigned int h);
	void setVisible(bool visible);
	void update();
};
