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

	eventHandler = [](Component* comp, ServerEvent* e) -> void {
		Container* cont = (Container*) comp;
		for(int i = 0; i < 64; i++) {
			Component* component = cont->components[i];
			if(component != NULL) {
				if(component->contains(e->mouse->xPos, e->mouse->yPos)) {
					e->mouse->xPos -= component->xPos;
					e->mouse->yPos -= component->yPos;
					component->handleEvent(e);
				}
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
