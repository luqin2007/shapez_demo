#pragma once

#include <map>

#include "GameMap.h"
#include "Timer.h"
#include "Common.h"

using std::max;
using std::min;
using std::map;

class Building;

constexpr int BUTTON_SIZE = 50;
constexpr int BUTTON_PADDING = 10;

class GameLogic
{
public:
	// 当前鼠标持有的建筑
	const Building* current_building = nullptr;
	Side current_side = Side::up;
	Vec2I current_building_data{ 0, 0 };
	map<string, const Building*> buildings;

	// 底部按钮
	map<string, Vec2I> buttons;
	Vec2I icon_bg0, icon_bg1;

	/**
	 * \brief 游戏初始化
	 * \param seed 游戏初始化种子
	 */
	void initialize(long long seed);

	void update();

	void destroy();

	GameMap& map()
	{
		return map_;
	}

	const GameMap& map() const
	{
		return map_;
	}

	Timer& timer()
	{
		return timer_;
	}

	/**
	 * \brief 按键按下
	 * \param key 按下的键
	 */
	void on_key_press(int key);

	/**
	 * \brief 重新计算底部按钮
	 * \param width 窗口宽
	 * \param height 窗口高
	 */
	void update_button_positions(int width, int height);

private:
	Timer timer_;
	GameMap map_;

	/**
	 * \brief 鼠标拖动
	 * \param dx 拖动距离 - x
	 * \param dy 拖动距离 - y
	 */
	void on_drag(float dx, float dy);

	/**
	 * \brief 左键点击
	 * \param x x
	 * \param y y
	 */
	void on_click_left(float x, float y);

	/**
	 * \brief 右键点击
	 * \param x x
	 * \param y y
	 */
	void on_click_right(float x, float y);

	/**
	 * \brief 中键点击
	 */
	void on_click_middle();

	/**
	 * \brief 滚轮滚动
	 * \param len 滚轮路程
	 */
	void on_wheel_roll(float len);
};
