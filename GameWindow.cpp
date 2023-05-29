#include <glad/glad.h>

#include "GameWindow.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "MouseHelper.h"

void GameWindow::create_window()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window_ = glfwCreateWindow(width_, height_, "Shapez Demo", nullptr, nullptr);
	glfwMakeContextCurrent(window_);

	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	glfwSwapInterval(1);
	glfwShowWindow(window_);

	on_resize(width_, height_);
}

void GameWindow::listen_events() const
{
	glfwSetMouseButtonCallback(window_, [](GLFWwindow*, const int button, const int action, int)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			MouseHelper::set_left_click(action != GLFW_RELEASE);
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			MouseHelper::set_mid_click(action != GLFW_RELEASE);
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			MouseHelper::set_right_click(action != GLFW_RELEASE);
		}
	});

	glfwSetCursorPosCallback(window_, [](GLFWwindow*, const double x, const double y)
	{
		MouseHelper::set_position(x, y);
		current_window->update_window_title();
	});

	glfwSetScrollCallback(window_, [](GLFWwindow*, double, const double y)
	{
		MouseHelper::set_wheel(y);
		current_window->update_window_title();
	});

	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow*, const int width, const int height)
	{
		current_window->on_resize(width, height);
	});

	glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			current_window->on_key_press(key);
		}
	});
}

void GameWindow::on_key_press(const int key)
{
	if (current_game)
	{
		current_game->on_key_press(key);
	}
}

void GameWindow::update_window_title()
{
	if (current_game)
	{
		char buf[300];
		auto& center = current_game->map().center;
		float mx = MouseHelper::x();
		float my = MouseHelper::y();
		float cell_size = current_game->map().cell_size;
		int gx = static_cast<int>(center.x - (width_ / 2.0f - mx) / cell_size);
		int gy = static_cast<int>(center.y - (height_ / 2.0f - my) / cell_size);
		sprintf_s(buf, "Shapez Demo %dx%d center=(%.2f,%.2f) cursor=(%.2f,%.2f on window)/(%d,%d on map) CellSize=%.2f",
		          width_, height_, center.x, center.y, mx, my, gx, gy, cell_size);
		glfwSetWindowTitle(current_window->window(), buf);
	}
}

void GameWindow::destroy() const
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void GameWindow::on_resize(const int width, const int height)
{
	width_ = width;
	height_ = height;
	glViewport(0, 0, width, height);
	
	if (current_renderer)
	{
		current_renderer->on_resize(width, height);
	}

	// 更新标题栏
	update_window_title();

	// 更新 UI 位置
	const int x0 = (width - 720) / 2;
	const int y0 = height - 80, y1 = y0 + 50;
	button_p0.x = x0;
	button_p0.y = y0;
	button_p1.x = x0 + 720;
	button_p1.y = y0 + button_size;

	constexpr int div = 70;
	int p0 = x0 + 20;

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

bool GameWindow::is_active() const
{
	return !glfwWindowShouldClose(window_);
}

void GameWindow::close() const
{
	glfwSetWindowShouldClose(window_, true);
}
