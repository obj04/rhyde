#pragma once

#include <chrono>
#include <ctime>


namespace currentTime {
	long nanos() {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
	}

	long micros() {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
	}

	long millis() {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	}

	long seconds() {
		long now = time(0);
		return localtime(&now)->tm_sec;
	}

	long minutes() {
		long now = time(0);
		return localtime(&now)->tm_min;
	}

	long hours() {
		long now = time(0);
		return localtime(&now)->tm_hour;
	}
}
