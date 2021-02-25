#include "Lock.hpp"
#include <mutex>


Lock::Lock() {
	mtx = new std::mutex();
}

void Lock::acquire() {
	((std::mutex*) mtx)->lock();
}

void Lock::release() {
	((std::mutex*) mtx)->unlock();
}
