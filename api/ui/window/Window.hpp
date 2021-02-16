#pragma once

#include "../../Client.hpp"
#include "../../../lib/Request.hpp"
#include "../../../lib/Graphics.hpp"


class Window: public Canvas {
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
