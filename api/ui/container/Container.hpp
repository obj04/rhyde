#pragma once

#include "../../../lib/Graphics.hpp"
#include "../component/Component.hpp"


class Container: public Component {
	public:
	Component* components[64];

	public:
	Container();
	void add(Component* comp, void* l = NULL);
	void remove(Component* comp);
};