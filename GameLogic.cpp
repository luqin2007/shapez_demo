#include "GameLogic.h"

GameLogic* current_game = nullptr;

LRESULT handle_window_message(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (!current_game) return HIWINDOW_DEFAULT_PROC;
	switch (msg)
	{
	default: return HIWINDOW_DEFAULT_PROC;
	}
}

void GameLogic::initialize(long long seed)
{
	current_timer = &timer_;
	map_.initialize(seed);
	current_game = this;
	hiex::SetWndProcFunc(hiex::GetHWnd_win32(), handle_window_message);
}

void GameLogic::update()
{
	// ЪѓБъзѓМќаЃбщ
	ExMessage mouse_msg = getmessage(EX_MOUSE);
	drag_helper_.UpdateMessage(mouse_msg);
	if (drag_helper_.IsLeftDrag())
	{
		on_drag(drag_helper_.GetDragX(), drag_helper_.GetDragY());
		is_left_clicked_ = false;
	}
	else if (mouse_msg.lbutton)
	{
		is_left_clicked_ = true;
	}
	else if (is_left_clicked_)
	{
		is_left_clicked_ = false;
		on_click(mouse_msg.x, mouse_msg.y);
	}

	if (mouse_msg.wheel)
	{
		on_wheel_roll(mouse_msg.wheel);
	}

	timer_.update();
}

void GameLogic::on_drag(int dx, int dy)
{
	map_.center.x -= dx / map_.cell_size;
	map_.center.y -= dy / map_.cell_size;
}

void GameLogic::on_click(short x, short y)
{
}

void GameLogic::on_wheel_roll(short len)
{
	map_.cell_size = max(20.0f, map_.cell_size + len / 15.0f);
}

GameMap& GameLogic::map()
{
	return map_;
}
