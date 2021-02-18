#pragma once

#include <queue>
using namespace std;


class Queue {
	queue<void*> q;

	public:
	void push(void* item);
	void* pop();
	bool isEmpty();
};
