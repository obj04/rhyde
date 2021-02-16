#pragma once

#include <chrono>
#include <ctime>


class Clock {
	public:
	static long getNanos();
	static long getMicros();
	static long getMillis();
	static long getSeconds();
	static long getMinutes();
	static long getHours();
};
