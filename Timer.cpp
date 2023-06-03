#include "Timer.h"

void Timer::update()
{
	previous_ms = current_ms;
	current_ms = time();

	// 更新时间间隔
	delta_ms = (current_ms - previous_ms) * time_multiply_;
	running_ms += delta_ms;
	delta = static_cast<float>(delta_ms) / 1000.0f;
	running = static_cast<float>(running_ms) / 1000.0f;
}

void Timer::reset()
{
	start_ms = time();
	current_ms = start_ms;
	previous_ms = start_ms;

	running_ms = 0;
	running = 0;

	delta_ms = 0;
	delta = 0;
}

long long Timer::time()
{
	using namespace std::chrono;
	return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() / 1000;
}
