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

	[[nodiscard]] GLFWwindow* window() const
	{
		return window_;
	}

	[[nodiscard]] int width() const
	{
		return width_;
	}
	
	[[nodiscard]] int height() const
	{
		return height_;
	}

	void update_window_title() const;
	
private:
	GLFWwindow* window_ = nullptr;
	int width_ = 1024, height_ = 768;

	void create_window();

	void listen_events() const;
};
