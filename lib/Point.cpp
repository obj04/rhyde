#include "Point.hpp"


Point::Point(int xPos, int yPos) {
	x = xPos;
	y = yPos;
}

void Point::move(Point diff) {
	move(diff.x, diff.y);
}

void Point::move(int xDiff, int yDiff) {
	x += xDiff;
	y += yDiff;
}
