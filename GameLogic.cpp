#include "GameLogic.h"

#include "GameRenderer.h"
#include "GameWindow.h"
#include "MouseHelper.h"

#include "Balancer.h"
#include "Belt.h"
#include "Cutter.h"
#include "Hub.h"
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
	mouse_.initialize();

	// 初始化建筑
	buildings["miner"] = &Miner::instance();
	buildings["belt"] = &Belts::direct();
	buildings["belt_left"] = &Belts::left();
	buildings["belt_right"] = &Belts::right();
	buildings["balancer"] = &Balancer::instance();
	buildings["rotater"] = &Rotaters::cw();
	buildings["rotater_ccw"] = &Rotaters::ccw();
	buildings["miner"] = &Miner::instance();
	buildings["underground_belt"] = &UndergroundBelt1::instance();
	buildings["underground_belt2"] = &UndergroundBelt2::instance();
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
	// 更新计时器
	timer_.update();

	// 更新鼠标响应
	if (mouse_.is_left_drag())
	{
		right_drag_time_ = 0;
		on_drag(mouse_.dx(), mouse_.dy());
	}
	else if (mouse_.is_left_clicked())
	{
		right_drag_time_ = 0;
		on_click_left(mouse_.x(), mouse_.y());
	}
	else if (mouse_.is_right_drag())
	{
		right_drag_time_ += timer_.delta_ms;
		on_right_drag(mouse_.dx(), mouse_.dy());
	}
	else if (mouse_.is_right_clicked())
	{
		right_drag_time_ = 0;
		on_click_right(mouse_.x(), mouse_.y());
	}
	else
	{
		right_drag_time_ = 0;
	}

	if (mouse_.is_mid_clicked())
	{
		on_click_middle();
	}

	on_wheel_roll(mouse_.wheel());
	mouse_.update();

	// 更新建筑
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			if (auto* b = map_.get_building(i, j))
			{
				b->building.update(*b, map_);
			}
		}
	}
}

void GameLogic::destroy()
{
	// 保存存档
	// 销毁地图
	map_.destroy();
}

void GameLogic::on_drag(const float dx, const float dy)
{
	if (current_building)
	{
		// 拖放建筑
		const float x = mouse_.x();
		const float y = mouse_.y();
		const int mx = static_cast<int>(map_.center.x - (current_window->width() / 2.0f - x) / map_.cell_size);
		const int my = static_cast<int>(map_.center.y - (current_window->height() / 2.0f - y) / map_.cell_size);
		map_.set_building(my, mx, current_building, current_side);
	}
	else
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
}

void GameLogic::on_right_drag(float dx, float dy)
{
	if (current_building)
	{
		// 取消建筑放置
		current_building = nullptr;
		glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (right_drag_time_ >= 500) // 500ms 后再移除
	{
		// 移除建筑
		const int mx = static_cast<int>(map_.center.x - (current_window->width() / 2.0f - mouse_.x()) / map_.
			cell_size);
		const int my = static_cast<int>(map_.center.y - (current_window->height() / 2.0f - mouse_.y()) / map_.
			cell_size);
		map_.remove_building(my, mx);
	}
}

void GameLogic::on_click_left(const float x, const float y)
{
	if (current_window)
	{
		// 放置建筑
		if (current_building)
		{
			const int mx = static_cast<int>(map_.center.x - (current_window->width() / 2.0f - x) / map_.cell_size);
			const int my = static_cast<int>(map_.center.y - (current_window->height() / 2.0f - y) / map_.cell_size);
			map_.set_building(my, mx, current_building, current_side);
		}
		else
		{
			// 选择建筑
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
			current_side = cw(current_side);
		}
		break;
	case GLFW_KEY_T:
		if (current_building)
		{
			current_building = current_building->next_variant;
		}
		break;
	case GLFW_KEY_UP:
		// 更新屏幕中心位置
		map_.center.y = map_.center.y - 1;

		if (current_renderer && current_window)
		{
			// 更新渲染
			current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
			// 更新标题栏
			current_window->update_window_title();
		}
		break;
	case GLFW_KEY_DOWN:
		// 更新屏幕中心位置
		map_.center.y = map_.center.y + 1;

		if (current_renderer && current_window)
		{
			// 更新渲染
			current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
			// 更新标题栏
			current_window->update_window_title();
		}
		break;
	case GLFW_KEY_LEFT:
		// 更新屏幕中心位置
		map_.center.x = map_.center.x + 1;

		if (current_renderer && current_window)
		{
			// 更新渲染
			current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
			// 更新标题栏
			current_window->update_window_title();
		}
		break;
	case GLFW_KEY_RIGHT:
		// 更新屏幕中心位置
		map_.center.x = map_.center.x - 1;

		if (current_renderer && current_window)
		{
			// 更新渲染
			current_renderer->update_cell_position(map_, current_window->width(), current_window->height());
			// 更新标题栏
			current_window->update_window_title();
		}
		break;
	case GLFW_KEY_KP_ADD:
		timer().time_multiply_ += 0.5f;

		if (current_window)
		{
			// 更新标题栏
			current_window->update_window_title();
		}
		break;
	case GLFW_KEY_KP_DECIMAL:
		if (timer().time_multiply_ > 0.5f)
		{
			timer().time_multiply_ -= 0.5f;
		}

		if (current_window)
		{
			// 更新标题栏
			current_window->update_window_title();
		}
		break;
	case GLFW_KEY_PAGE_UP:
		// 跳关 调试用
		{
		HubContext* ctx = static_cast<HubContext*>(map_.get_building(CELL_COUNT / 2, CELL_COUNT / 2));
		ctx->accept_count = ctx->total_count;
		}
		break;
	default:
		break;
	}
}

void GameLogic::update_button_positions(const int width, const int height)
{
	constexpr int padding_x = 0;
	constexpr int div = 70;

	// 更新 UI 位置
	const int x0 = (width - 680) / 2;
	const int y0 = height - 80;
	icon_bg0.x = x0 - BUTTON_PADDING - padding_x;
	icon_bg0.y = y0 - BUTTON_PADDING;
	icon_bg1.x = x0 + 680 + BUTTON_PADDING + padding_x;
	icon_bg1.y = y0 + BUTTON_SIZE + BUTTON_PADDING;

	int p0 = x0 + padding_x;
	buttons["miner"] = Vec2I{p0, y0};
	p0 += div;
	buttons["belt"] = Vec2I{p0, y0};
	p0 += div;
	buttons["balancer"] = Vec2I{p0, y0};
	p0 += div;
	buttons["rotater"] = Vec2I{p0, y0};
	p0 += div;
	buttons["underground_belt"] = Vec2I{p0, y0};
	p0 += div;
	buttons["cutter"] = Vec2I{p0, y0};
	p0 += div;
	buttons["mixer"] = Vec2I{p0, y0};
	p0 += div;
	buttons["painter"] = Vec2I{p0, y0};
	p0 += div;
	buttons["stacker"] = Vec2I{p0, y0};
	p0 += div;
	buttons["trash"] = Vec2I{p0, y0};
}
