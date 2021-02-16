#include "Clock.hpp"


long Clock::getNanos() {
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
}

long Clock::getMicros() {
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

long Clock::getMillis() {
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

long Clock::getSeconds() {
	long now = time(0);
	return localtime(&now)->tm_sec;
}

long Clock::getMinutes() {
	long now = time(0);
	return localtime(&now)->tm_min;
}

long Clock::getHours() {
	long now = time(0);
	return localtime(&now)->tm_hour;
}
