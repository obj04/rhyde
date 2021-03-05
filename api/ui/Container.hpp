#pragma once

#include "Component.hpp"


class Container: public Component {
	public:
	Component* components[64];

	public:
	Container(API* ptr);
	void add(Component* comp, void* l = NULL);
	void remove(Component* comp);
};
