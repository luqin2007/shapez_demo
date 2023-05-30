#include "GameLogic.h"

#include "GameRenderer.h"
#include "GameWindow.h"
#include "MouseHelper.h"

#include "Balancer.h"
#include "Belt.h"
#include "Cutter.h"
#include "Miner.h"
#include "Mixer.h"
#include "Painter.h"
#include "Rotater.h"
#include "Stacker.h"
#include "Trash.h"
#include "UndergroundBelt1.h"

void GameLogic::initialize(const long long seed)
{
	current_game = this;
	// 初始化随机数种子、计时器、鼠标及地图等游戏数据
	random_seed(seed);
	timer_.reset();
	map_.initialize();
	MouseHelper::initialize();

	// 初始化建筑
	buildings["miner"] = &Miner::instance();
	buildings["belt"] = &Belts::direct();
	buildings["balancer"] = &Balancer::instance();
	buildings["rotater"] = &Rotaters::cw();
	buildings["miner"] = &Miner::instance();
	buildings["underground_belt"] = &UndergroundBelt1::instance();
	buildings["cutter"] = &Cutter::instance();
	buildings["mixer"] = &Mixer::instance();
	buildings["painter"] = &Painter::instance();
	buildings["stacker"] = &Stacker::instance();
	buildings["trash"] = &Trash::instance();

	// 初始化屏幕大小相关计算
	update_button_positions(current_window->width(), current_window->height());
}

void GameLogic::update()
{
	timer_.update();

	if (MouseHelper::is_left_drag())
	{
		on_drag(MouseHelper::dx(), MouseHelper::dy());
	}
	else if (MouseHelper::is_left_clicked())
	{
		on_click_left(MouseHelper::x(), MouseHelper::y());
	}
	else if (MouseHelper::is_right_clicked())
	{
		on_click_right(MouseHelper::x(), MouseHelper::y());
	}

	if (MouseHelper::is_mid_clicked())
	{
		on_click_middle();
	}

	on_wheel_roll(MouseHelper::wheel());
	MouseHelper::update();
}

void GameLogic::destroy()
{
	// 保存存档
}

void GameLogic::on_drag(const float dx, const float dy)
{
	// 更新屏幕中心位置
	map_.center.x = map_.center.x - dx / map_.cell_size;
	map_.center.y = map_.center.y - dy / map_.cell_size;

	if (current_renderer && current_window)
	{
		// 更新渲染
		current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
		// 更新标题栏
		current_window->update_window_title();
	}
}

void GameLogic::on_click_left(const float x, const float y)
{
	if (current_window)
	{
		if (current_building)
		{
			const int mx = static_cast<int>(map_.center.x - (current_window->width() / 2.0f - x) / map_.cell_size);
			const int my = static_cast<int>(map_.center.y - (current_window->height() / 2.0f - y) / map_.cell_size);
			cout << mx << " " << my << endl;
			if (map_.set_building(my, mx, current_building, current_side))
			{
				current_building = nullptr;
				current_side = Side::up;
				glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
		else
		{
			for (const auto& [name, p] : buttons)
			{
				if (is_in(p.x, x, BUTTON_SIZE) && is_in(p.y, y, BUTTON_SIZE))
				{
					current_building = buildings[name];
					current_side = Side::up;
					glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
					break;
				}
			}
		}
	}
}

void GameLogic::on_click_right(const float x, const float y)
{
	if (current_building)
	{
		// 取消建筑放置
		current_building = nullptr;
		glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		// 移除建筑
		const int mx = static_cast<int>(map_.center.x - (current_window->width() / 2.0f - x) / map_.cell_size);
		const int my = static_cast<int>(map_.center.y - (current_window->height() / 2.0f - y) / map_.cell_size);
		map_.remove_building(my, mx);
	}
}

void GameLogic::on_click_middle()
{
	// 更新屏幕中心位置
	current_game->map().center.x = CELL_COUNT / 2.0f;
	current_game->map().center.y = CELL_COUNT / 2.0f;
	// 更新渲染
	if (current_renderer && current_window)
	{
		current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
	}
	// 更新标题栏
	current_window->update_window_title();
}

void GameLogic::on_wheel_roll(const float len)
{
	if (!feq(len, 0))
	{
		// 更新网格大小
		map_.cell_size = max(5.0f, map_.cell_size + len * 2);
		// 更新渲染
		if (current_renderer && current_window)
		{
			current_renderer->update_cell_size(map_);
			current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
		}
		// 更新标题栏
		current_window->update_window_title();
	}
}

void GameLogic::on_key_press(const int key)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (current_building)
		{
			current_building = nullptr;
			glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		break;
	case GLFW_KEY_R:
		if (current_building)
		{
			current_side = ++current_side;
		}
		break;
	case GLFW_KEY_Y:
		if (current_building)
		{
			current_building = current_building->next_variant;
		}
		break;
	default:
		break;
	}
}

void GameLogic::update_button_positions(const int width, const int height)
{

	// 更新 UI 位置
	const int x0 = (width - 720) / 2;
	const int y0 = height - 80;
	button_p0.x = x0;
	button_p0.y = y0;
	button_p1.x = x0 + 720;
	button_p1.y = y0 + BUTTON_SIZE;

	constexpr int div = 70;
	int p0 = x0 + 20;

	buttons["miner"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["belt"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["balancer"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["rotater"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["underground_belt"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["cutter"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["mixer"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["painter"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["stacker"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["trash"] = Vec2I{ p0, y0 };
}
