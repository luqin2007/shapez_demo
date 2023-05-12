#include "GameLogic.h"

void GameLogic::initialize(const long long seed)
{
	current_game = this;

	timer_.reset();
	map_.initialize(seed);
	MouseHelper::initialize();
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

	if (MouseHelper::is_mid_clicked())
	{
		on_click_middle();
	}

	on_wheel_roll(MouseHelper::wheel());
	MouseHelper::update();
}

void GameLogic::on_drag(const float dx, const float dy)
{
	map_.center.x = map_.center.x - dx / map_.cell_size;
	map_.center.y = map_.center.y - dy / map_.cell_size;
}

void GameLogic::on_click_left(float x, float y)
{
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
