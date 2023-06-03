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
	});

	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow*, const int width, const int height)
	{
		current_window->on_resize(width, height);
	});

	glfwSetKeyCallback(window_, [](GLFWwindow*, const int key, int, const int action, int)
	{
		if ((action == GLFW_PRESS || action == GLFW_REPEAT) && current_game)
		{
			current_game->on_key_press(key);
		}
	});
}

void GameWindow::update_window_title() const
{
	if (current_game && current_renderer)
	{
		char buf[300];
		const auto& center = current_game->map().center;
		const float mx = MouseHelper::x();
		const float my = MouseHelper::y();
		const float cell_size = current_game->map().cell_size;
		const int gx = center.x - (width_ / 2.0f - mx) / cell_size;
		const int gy = center.y - (height_ / 2.0f - my) / cell_size;
		if (sprintf_s(
			buf, "Shapez Demo %dx%d center=(%.2f,%.2f) cursor=(%.2f,%.2f)/(%d,%d) cell=%.2f render=(%d,%d)-(%d,%d) time-mul=%.1f",
			width_, height_, center.x, center.y, mx, my, gx, gy, cell_size, 
			current_renderer->cell0_.x, current_renderer->cell0_.y, current_renderer->cell1_.x, current_renderer->cell1_.y, current_game->timer().time_multiply_))
		{
			glfwSetWindowTitle(current_window->window(), buf);
		}
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

	// 更新按钮
	if (current_game)
	{
		current_game->update_button_positions(width, height);
	}

	// 更新渲染器
	if (current_renderer)
	{
		AbstractDrawer::resize(width, height);
		current_renderer->update_cell_position(current_game->map(), width, height);
	}

	// 更新标题栏
	update_window_title();
}

bool GameWindow::is_active() const
{
	return !glfwWindowShouldClose(window_);
}

void GameWindow::close() const
{
	glfwSetWindowShouldClose(window_, true);
}
