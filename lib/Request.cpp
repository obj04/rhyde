#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "Request.hpp"


Request::Request() {
	elementsCount = 0;
}

Request::Request(char* data) {
	elementsCount = 0;
	unsigned int pos = 4;
	while(pos < ((unsigned int*) data)[0]) {
		unsigned int size = ((unsigned int*) &data[pos])[0];
		pos += 4;
		char object[size];
		memcpy(object, &data[pos], size);
		pos += size;
		addObject(object, size);
	}
}

Request::Request(int fd) {
	elementsCount = 0;

	int n = 0;
	int requestSize;
	char header[4];
	do {
		n += read(fd, &header[n], 4 - n);
	} while(n < 4);
	memcpy(&requestSize, header, 4);
	char data[requestSize];
	while(n < requestSize) {
		n += read(fd, &data[n], requestSize - n);
	}

	int pos = 4;
	while(pos < requestSize) {
		unsigned int size = ((unsigned int*) &data[pos])[0];
		pos += 4;
		addObject(&data[pos], size);
		pos += size;
	}
}

void Request::addObject(void* object, unsigned int size) {
	elements[elementsCount].object = new char[size];
	elements[elementsCount].size = size;
	memcpy(elements[elementsCount].object, object, size);
	elementsCount++;
}

void Request::addObject(int object) {
	elements[elementsCount].object = new char[4];
	elements[elementsCount].size = 4;
	((int*) elements[elementsCount].object)[0] = object;
	elementsCount++;
}

Request::Element Request::getObject(unsigned int index) {
	return elements[index];
}

int Request::getIntValue(unsigned int index) {
	return *((unsigned int*) (elements[index].object));
}

void Request::send(int clientfd) {
	unsigned int requestSize = 4;
	for(Element e : elements)
		if(e.size != 0)
			requestSize += e.size + 4;
	char data[requestSize];
	unsigned int pos = 4;
	memcpy(data, &requestSize, 4);
	for(Element e : elements) {
		if(e.size != 0) {
			((unsigned int*) &data[pos])[0] = e.size;
			pos += 4;
			memcpy(&data[pos], e.object, e.size);
			pos += e.size;
		}
	}
	write(clientfd, data, requestSize);
}
