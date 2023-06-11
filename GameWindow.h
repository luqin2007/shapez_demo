#pragma once

#include <map>
#include <string>

#include <GLFW/glfw3.h>

#include "Common.h"
#include "vec.h"

using std::map;
using std::string;

class Building;

/**
 * \brief 游戏窗口
 */
class GameWindow
{
public:
	/**
	 * \brief 初始化窗口
	 */
	void initialize()
	{
		current_window = this;
		create_window();
		listen_events();
	}

	/**
	 * \brief 游戏窗口大小变化时触发
	 * \param width 新宽度
	 * \param height 新高度
	 */
	void on_resize(int width, int height);

	/**
	 * \brief 判断窗口是否存活
	 * \return 是否存活
	 */
	[[nodiscard]]
	bool is_alive() const;

	/**
	 * \brief 销毁窗口，释放资源
	 */
	void destroy() const;

	/**
	 * \brief 获取 GLFW 窗口句柄
	 * \return GLFW 窗口句柄
	 */
	[[nodiscard]] GLFWwindow* window() const
	{
		return window_;
	}

	[[nodiscard]] int width() const
	{
		return width_;
	}

	/**
	 * \brief 宽度
	 * \return 窗口宽度
	 */
	[[nodiscard]] int height() const
	{
		return height_;
	}

	/**
	 * \brief 刷新窗口标题
	 */
	void update_window_title() const;
	
private:
	GLFWwindow* window_ = nullptr;
	int width_ = 1024, height_ = 768;

	void create_window();

	void listen_events() const;
};
