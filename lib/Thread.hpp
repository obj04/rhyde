#pragma once

#include <pthread.h>


class Thread {
	pthread_t thread;
	void* (*run)(void*);
	void* args;
	
	public:
	Thread(void* (*function)(void*), void* arguments);
	Thread* start();
	void join();
	void detach();
};
