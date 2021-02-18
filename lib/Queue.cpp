#include "Queue.hpp"


 void Queue::push(void* item) {
	q.push(item);
}

void* Queue::pop() {
	void* item = q.front();
	q.pop();
	return item;
}

bool Queue::isEmpty() {
	return q.empty();
}
