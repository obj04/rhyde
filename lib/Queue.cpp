#include "Queue.hpp"
#include <cstdio>


void Queue::push(void* item) {
	q.push(item);
}

void* Queue::pop() {
	void* item = q.front();
	q.pop();
	return item;
}

bool Queue::isEmpty() {
	bool result = q.empty();
	return result;
}
