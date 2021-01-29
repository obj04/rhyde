#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>


class Thread {
	pthread_t thread;
	void* (*run)(void*);
	void* args;
	
	public:
	Thread(void* (*function)(void*), void* arguments) {
		run = function;
		args = arguments;
	}
	
	Thread* start() {
		pthread_create(&thread, NULL, run, args);
		return this;
	}
	
	void join() {
		pthread_join(thread, NULL); //void** retval
	}
	
	void detach() {
		pthread_detach(thread);
	}
};

#endif