#pragma once

#include "Client.hpp"
#include "ui/component/Component.hpp"
#include "../lib/List.hpp"
#include "../lib/ServerEvent.hpp"


class API {
	public:
	Client* client;
	List* components = new List();
	void (*eventListener)(void* v, ServerEvent* e);

	API();
	~API();
	void connect(char* host, int port);
	Conversation* send(Request* r);
	void registerComponent(Component* c);
	void unregisterComponent(Component* c);
};
