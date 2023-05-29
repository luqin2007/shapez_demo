#include "GameLogic.h"

#include "GameRenderer.h"
#include "GameWindow.h"
#include "MouseHelper.h"

#include "BuildingBalancer.h"
#include "BuildingBelt.h"
#include "BuildingCutter.h"
#include "BuildingMiner.h"
#include "BuildingMixer.h"
#include "BuildingPainter.h"
#include "BuildingRotater.h"
#include "BuildingStacker.h"
#include "BuildingTrash.h"
#include "BuildingUndergroundBelt1.h"

void GameLogic::initialize(const long long seed)
{
	current_game = this;
	random_seed(seed);
	timer_.reset();
	map_.initialize();
	MouseHelper::initialize();

	buildings["miner"] = &BuildingMiner::instance();
	buildings["belt"] = &BuildingBelt::instance();
	buildings["balancer"] = &BuildingBalancer::instance();
	buildings["rotater"] = &BuildingRotaterL::instance();
	buildings["miner"] = &BuildingMiner::instance();
	buildings["underground_belt"] = &BuildingUndergroundBelt1::instance();
	buildings["cutter"] = &BuildingCutter::instance();
	buildings["mixer"] = &BuildingMixer::instance();
	buildings["painter"] = &BuildingPainter::instance();
	buildings["stacker"] = &BuildingStacker::instance();
	buildings["trash"] = &BuildingTrash::instance();
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

void GameLogic::on_resize(const int width, const int height)
{
	width_ = width;
	height_ = height;
}

void GameLogic::on_drag(const float dx, const float dy)
{
	map_.center.x = map_.center.x - dx / map_.cell_size;
	map_.center.y = map_.center.y - dy / map_.cell_size;
}

void GameLogic::on_click_left(const float x, const float y)
{
	if (current_window)
	{
		if (current_building)
		{
			const int mx = static_cast<int>(map_.center.x - width_ / 2.0f + x);
			const int my = static_cast<int>(map_.center.y - height_ / 2.0f + y);
			if (map_.set_building(mx, my, current_building, current_side))
			{
				current_building = nullptr;
				current_side = Side::up;
			}
		}
		else
		{
			for (const auto& [name, p] : current_window->buttons)
			{
				if (is_in(p.x, x, GameWindow::button_size_f) && is_in(p.y, y, GameWindow::button_size_f))
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
		current_building = nullptr;
		glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		const int mx = static_cast<int>(map_.center.x - width_ / 2.0f + x);
		const int my = static_cast<int>(map_.center.y - height_ / 2.0f + y);
		map_.remove_building(mx, my);
	}
}

void GameLogic::on_click_middle()
{
	current_game->map().center.x = CELL_COUNT / 2;
	current_game->map().center.y = CELL_COUNT / 2;
}

void GameLogic::on_wheel_roll(const float len)
{
	map_.cell_size = max(5.0f, map_.cell_size + len * 2);
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
