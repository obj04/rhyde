#pragma once

#include <queue>
using namespace std;
#include "Lock.hpp"


class Queue {
	queue<void*> q;

	public:
	void push(void* item);
	void* pop();
	bool isEmpty();
};
