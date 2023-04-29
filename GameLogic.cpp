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
		on_click(MouseHelper::x(), MouseHelper::y());
	}
	on_wheel_roll(MouseHelper::wheel());
	MouseHelper::update();
}

void GameLogic::on_drag(const float dx, const float dy)
{
	map_.center.x -= dx / map_.cell_size;
	map_.center.y += dy / map_.cell_size;
}

void GameLogic::on_click(float x, float y)
{
}

void GameLogic::on_wheel_roll(const float len)
{
	map_.cell_size = max(20.0f, map_.cell_size + len * 5);
}
