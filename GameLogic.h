#pragma once

#include "GameMap.h"
#include "Timer.h"
#include "Common.h"

using std::max;
using std::min;

class GameLogic
{
public:
	/**
	 * \brief 游戏初始化
	 * \param seed 游戏初始化种子
	 */
	void initialize(long long seed);

	void update();

	void destroy();

	void on_resize(const int width, const int height);

	GameMap& map()
	{
		return map_;
	}

	Timer& timer()
	{
		return timer_;
	}

private:
	Timer timer_;
	GameMap map_;

	int width_ = 0, height_ = 0;

	// 当前鼠标持有的建筑
	int current_building_ = 0;
	int current_building_variant_ = 0;
	Side current_side_ = Side::up;
	Vec2I data_{0, 0};

	void on_drag(float dx, float dy);

	void on_click_left(float x, float y);

	void on_click_middle();

	void on_wheel_roll(float len);
};
