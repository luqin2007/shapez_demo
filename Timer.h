#pragma once

#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	long long previous;
	long long current;
	long long delta_ms;
	float delta;

	void update();
	void reset();
};

