#pragma once

#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	long long start_ms;
	long long previous_ms = 0;
	long long current_ms = 0;
	long long delta_ms = 0;
	long long running_ms = 0;

	float delta = 0;
	float running = 0;

	void update();
	void reset();
};
