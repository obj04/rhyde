#include "Lock.hpp"


Lock::Lock() {
	count = 0;
}

void Lock::acquire() {
	count++;
	while(count > 1);
}

void Lock::release() {
	count--;
}
