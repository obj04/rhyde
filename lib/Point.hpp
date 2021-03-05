#pragma once


class Point {
	public:
	int x;
	int y;

	Point(int xPos, int yPos);
	void move(Point diff);
	void move(int xDiff, int yDiff);
};
