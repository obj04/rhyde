#include "Thread.hpp"


Thread::Thread(void* (*function)(void*), void* arguments) {
	run = function;
	args = arguments;
}

Thread* Thread::start() {
	pthread_create(&thread, NULL, run, args);
	return this;
}

void Thread::join() {
	pthread_join(thread, NULL); //void** retval
}

void Thread::detach() {
	pthread_detach(thread);
}
