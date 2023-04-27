#pragma once

#include "HiEasyX.h"
#include "HiEasyX/HiMouseDrag.h"
#include "GameMap.h"
#include "Timer.h"

class GameLogic;

extern GameLogic* current_game;

extern LRESULT CALLBACK handle_window_message(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

class GameLogic
{
public:
	void initialize(long long seed);

	void update();

	void on_drag(int dx, int dy);

	void on_click(short x, short y);

	void on_wheel_roll(short len);

	GameMap& map();

private:
	Timer timer_;
	GameMap map_;

	// mouse
	bool is_left_clicked_ = false;
	hiex::MouseDrag drag_helper_;
};
