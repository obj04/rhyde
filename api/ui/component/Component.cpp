#include "Component.hpp"


void Component::render() {
	if(renderer != NULL)
		renderer(this);
}