#include "Timer.h"

void Timer::update()
{
	previous_ms = current_ms;
	current_ms = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

	delta_ms = current_ms - previous_ms;
	delta = delta_ms / 1000.0f;

	running_ms = current_ms - start_ms;
	running = running_ms / 1000.0f;
}

void Timer::reset()
{
	start_ms = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	current_ms = start_ms;
	previous_ms = start_ms;

	running_ms = 0;
	running = 0;

	delta_ms = 0;
	delta = 0;
}
