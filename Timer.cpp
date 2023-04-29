#include "Timer.h"

void Timer::update()
{
	previous = current;
	const auto current_time = system_clock::now().time_since_epoch();
	current = duration_cast<microseconds>(current_time).count();
	delta_ms = current - previous;
	delta = delta_ms / 1000.0f;
}

void Timer::reset()
{
	update();
	previous = current;
	delta_ms = 0;
	delta = 0;
}
