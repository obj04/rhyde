#pragma once

#include "../api/Protocol.hpp"


class Request {
	public:
	typedef struct {
		unsigned int size = 0;
		char* object;
	} Element;
	Element elements[64];
	unsigned int elementsCount;

	Request();
	Request(int fd, bool blocking = true);
	Request(char* data);
	void addObject(void* object, unsigned int size);
	void addObject(int object);
	Element getObject(unsigned int index);
	int getIntValue(unsigned int index);
	void send(int clientfd);
};
