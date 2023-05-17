#pragma once

#include <string>
#include <iostream>
#include <filesystem>

#include <glad/glad.h>

#include "Resouces.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::filesystem::path;

/**
 * \brief GL 绘制类
 */
class AbstractDrawer
{
public:
	/**
	 * \brief 当窗口大小发生变化时调用
	 * \param width 窗口宽度
	 * \param height 窗口高度
	 */
	void resize(GLfloat width, GLfloat height) const;

	/**
	 * \brief 对绘制类共享资源的释放
	 */
	static void destroy_static();

protected:

	/**
	 * \brief 绘制使用的着色器程序
	 */
	GLuint program_ = 0;

	/**
	 * \brief 绘制使用的顶点数组对象
	 */
	GLuint vao_ = 0;

	/**
	 * \brief 顶点缓冲区对象
	 */
	GLuint buffer_ = 0;

	/**
	 * \brief 创建着色器程序
	 * \param program 着色器程序变量
	 * \param vert 顶点着色器变量
	 * \param frag 片元着色器变量
	 */
	static void create_program(GLuint& program, string&& vert, string&& frag);

	/**
	 * \brief 创建着色器
	 * \param type 着色器类型
	 * \param p 着色器路径
	 * \return 创建的着色器 id，创建失败则返回 0
	 */
	static GLuint create_shader(const GLenum type, const path& p);

	/**
	 * \brief 绑定用于绘制方块的顶点数组缓冲区
	 */
	static void bind_indices();

private:
	inline static GLuint indices_buffer_ = 0;
};

