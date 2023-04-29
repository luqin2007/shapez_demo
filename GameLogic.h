#pragma once

#include <cmath>

#include "GameMap.h"
#include "Timer.h"
#include "Common.h"
#include "MouseHelper.h"

using std::max;

class GameLogic
{
public:
	void initialize(long long seed);

	void update();

	GameMap& map()
	{
		return map_;
	}

	Timer& timer()
	{
		return timer_;
	}
	
private:
	Timer timer_ = {};
	GameMap map_;

	void on_drag(float dx, float dy);

	void on_click(float x, float y);

	void on_wheel_roll(float len);
};
