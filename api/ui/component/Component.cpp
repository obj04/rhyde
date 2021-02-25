#include "Component.hpp"


Component::Component(API* ptr) {
	api = ptr;
}

void Component::render() {
	if(renderer != NULL)
		renderer(this);
}

void Component::pack() {
	if(packer != NULL)
		packer(this);
}

void Component::handleEvent(ServerEvent* e) {
	if(eventHandler != NULL)
		eventHandler(this, e);
}
