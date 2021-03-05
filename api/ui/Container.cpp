#include "Container.hpp"


Container::Container(API* ptr): Component(ptr) {
	api = ptr;
	renderer = [](Component* comp) -> void {
		Container* cont = (Container*) comp;
		for(int i = 0; i < 64; i++) {
			if(cont->components[i] != NULL) {
				Component* c = cont->components[i];
				c->render();
				cont->assimilate(c->xPos, c->yPos, c->width, c->height, c->bitmap);
			}
		}
	};

	eventHandler = [](Component* comp, ServerEvent e) -> void {
		Container* cont = (Container*) comp;
		for(int i = 0; i < 64; i++) {
			Component* component = cont->components[i];
			if(component != NULL) {
				if(component->contains(e.mouse.xPos, e.mouse.yPos)) {
					e.mouse.xPos -= component->xPos;
					e.mouse.yPos -= component->yPos;
					component->handleEvent(e);
				}
			}
		}
	};

}

void Container::add(Component* comp, void* l) {
	comp->id = id;
	comp->parent = this;
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
			components[i]->id = 0;
			components[i]->parent = NULL;
			components[i] = NULL;
		}
	}
	lock->release();
}
