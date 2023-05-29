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
	});

	glfwSetScrollCallback(window_, [](GLFWwindow*, double, const double y)
	{
		MouseHelper::set_wheel(y);
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

	if (current_game)
	{
		current_game->on_resize(width, height);
	}

	if (current_renderer)
	{
		current_renderer->on_resize(width, height);
	}

	// 更新 UI 位置
	const int x0 = (width - 720) / 2;
	const int y0 = height - 80, y1 = y0 + 50;
	button_p0.x = x0;
	button_p0.y = y0;
	button_p1.x = x0 + 720;
	button_p1.y = y0 + button_size;

	constexpr int div = 70;
	int p0 = x0 + 20;

	buttons["miner"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["belt"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["balancer"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["rotater"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["underground_belt"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["cutter"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["mixer"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["painter"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["stacker"] = Vec2I{ p0, y0 };
	p0 += div;
	buttons["trash"] = Vec2I{ p0, y0 };
}

bool GameWindow::is_active() const
{
	return !glfwWindowShouldClose(window_);
}

void GameWindow::close() const
{
	glfwSetWindowShouldClose(window_, true);
}
