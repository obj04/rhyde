#pragma once

#include <list>
using namespace std;


class List {
	public:
	list<void*> items = list<void*>();

	List();
	void add(void* item);
	void remove(void* item);
};
