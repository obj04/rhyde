#include "API.hpp"


API::API() {
	eventListener = [](void* ptr, ServerEvent* e) -> void {
		API* api = (API*) ptr;
		for(void* c : api->components->items) {
			Component* comp = (Component*) c;
			if(comp != NULL) {
				if(comp->contains(e->mouse->xPos, e->mouse->yPos)) {
					e->mouse->xPos -= comp->xPos;
					e->mouse->yPos -= comp->yPos;
					comp->handleEvent(e);
				}
			}
		}
	};
}

API::~API() {
	delete client;
}

void API::connect(char* host, int port) {
	client = new Client(eventListener, this, host, port);
}

Conversation* API::send(Request* r) {
	Conversation* conv = new Conversation(r);
	conv->lock->acquire();
	client->requestsPending->push(conv);
	return conv;
}

void API::registerComponent(Component* c) {
	components->add(c);
}

void API::unregisterComponent(Component* c) {
	components->remove(c);
}
