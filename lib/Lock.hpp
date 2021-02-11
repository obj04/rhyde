#pragma once


class Lock {
	int count;

	public:
	Lock();
	void acquire();
	void release();
};
