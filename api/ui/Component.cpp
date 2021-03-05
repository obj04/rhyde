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

void Component::handleEvent(ServerEvent e) {
	if(e.source == e.MOUSE) {
		if(contains(xPos + e.mouse.xPos + e.mouse.xDiff, yPos + e.mouse.yPos + e.mouse.yDiff))
			hovered = true;
		else
			hovered = false;
		api->updateClientArea(this);
	}

	if(eventHandler != NULL)
		eventHandler(this, e);
}

Point Component::getAbsolutePosition() {
	Point pos = Point(xPos, yPos);
	if(parent != NULL)
		pos.move(parent->getAbsolutePosition());
	return pos;
}
