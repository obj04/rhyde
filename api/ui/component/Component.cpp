#include "Component.hpp"


void Component::render() {
	if(renderer != NULL)
		renderer(this);
}

void Component::handleEvent(ServerEvent* e) {
	if(eventHandler != NULL)
		eventHandler(this, e);
}
