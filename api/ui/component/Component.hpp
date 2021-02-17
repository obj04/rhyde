#pragma once

#include "../../../lib/Graphics.hpp"


class Component: public Canvas {
	protected:
	void (*renderer)(Component*);
	
	public:
	void render();
};