#include "GameWindow.h"

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
}

bool GameWindow::is_active() const
{
	return !glfwWindowShouldClose(window_);
}

void GameWindow::close() const
{
	glfwSetWindowShouldClose(window_, true);
}
