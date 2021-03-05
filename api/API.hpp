#pragma once

#include "Client.hpp"
#include "../lib/PSFFont.hpp"
#include "../lib/List.hpp"
#include "../lib/ServerEvent.hpp"


class API {
	public:
	Client* client;
	List* components = new List();
	void (*eventListener)(void* v, ServerEvent e);
	PSFFont* defaultFont;

	API();
	~API();
	void connect(char* host, int port);
	Conversation* send(Request* r);
	void updateClientArea(void* ptr);
};
