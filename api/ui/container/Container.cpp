#include "Container.hpp"


Container::Container() {
	renderer = [](Component* comp) -> void {
		Container* cont = (Container*) comp;
		for(int i = 0; i < 64; i++) {
			if(cont->components[i] != NULL) {
				Component* c = cont->components[i];
				cont->assimilate(c->xPos, c->yPos, c->width, c->height, c->bitmap);
			}
		}
	};
}

void Container::add(Component* comp, void* l) {
	for(int i = 0; i < 64; i++) {
		if(components[i] == NULL) {
			components[i] = comp;
			return;
		}
	}
}

void Container::remove(Component* comp) {
	lock->acquire();
	for(int i = 0; i < 64; i++) {
		if(components[i] == comp) {
			delete components[i];
			components[i] = NULL;
		}
	}
	lock->release();
}