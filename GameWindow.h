#pragma once

#include <map>
#include <string>

#include <GLFW/glfw3.h>

#include "Common.h"
#include "vec.h"

using std::map;
using std::string;

class Building;

class GameWindow
{
public:

	// UI
	// 底部按钮
	map<string, Vec2I> buttons;
	Vec2I button_p0, button_p1;
	constexpr static int button_size = 50;
	constexpr static float button_size_f = 50;

	void initialize()
	{
		current_window = this;
		create_window();
		listen_events();
	}

	void on_resize(int width, int height);

	[[nodiscard]]
	bool is_active() const;

	void close() const;

	void destroy() const;

	GLFWwindow* window() const
	{
		return window_;
	}

	[[nodiscard]]
	int width() const
	{
		return width_;
	}

	[[nodiscard]]
	int height() const
	{
		return height_;
	}

private:
	GLFWwindow* window_ = nullptr;
	int width_ = 1024, height_ = 768;

	void create_window();

	void listen_events() const;

	void on_key_press(int key);

	void update_window_title();
};
