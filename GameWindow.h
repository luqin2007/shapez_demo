#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Common.h"

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

	bool is_active() const;

	void close() const;

	void destroy() const;

	GLFWwindow* window() const
	{
		return window_;
	}

	int width() const
	{
		return width_;
	}

	int height() const
	{
		return height_;
	}

private:
	GLFWwindow* window_ = nullptr;
	int width_ = 1024, height_ = 768;

	void create_window();

	void listen_events() const;
};
