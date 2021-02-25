#pragma once


class Lock {
	void* mtx;

	public:
	Lock();
	void acquire();
	void release();
};
