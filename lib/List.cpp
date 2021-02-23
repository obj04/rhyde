#include "List.hpp"


List::List() {}

void List::add(void* item) {
	items.push_back(item);
}

void List::remove(void* item) {
	items.remove(item);
}
