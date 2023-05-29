#pragma once

#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <exception>

#include <glad/glad.h>

using std::map;
using std::string;
using std::filesystem::path;
using std::cout;
using std::endl;
using std::exception;

/**
 * \brief 表示地图集中的一个图片
 */
struct Rect
{
	float u, v, w, h;
};

/**
 * \brief 地图集，将多张图片集合到一张图中，要求每张图片的大小相同或相近
 */
class Atlas
{
public:
	Atlas(const float width, const float height, const int cell_width, const int cell_height, const bool m4 = false):
		width_(width), height_(height), cell_width_(cell_width), cell_height_(cell_height),
		count_per_row_(static_cast<int>(width) / cell_width), count_per_col_(static_cast<int>(height) / cell_height),
		index_(image_id_++), m4_(m4)
	{
	}

	Atlas(const float size, const int cell_size, const bool m4 = false) : Atlas(size, size, cell_size, cell_size, m4)
	{
	}

	/**
	 * \brief 初始化
	 */
	void initialize();

	/**
	 * \brief 销毁
	 */
	void destroy() const;

	operator GLint() const
	{
		return index_;
	}

	/**
	 * \brief 向地图集中导入图片，应当在 initialize 方法之后调用
	 * \param p 图片完整路径
	 * \return 当前地图集
	 */
	Atlas& operator<<(const path& p);

	/**
	 * \brief 地图集生成完成时调用
	 * \param gen_mipmap 是否需要生成 mipmap
	 * \return 当前地图集
	 */
	Atlas& operator<<(const bool gen_mipmap);

	const Rect& operator[](const string& name);

	const Rect& operator[](const char* name);

private:
	const float width_, height_;
	const int cell_width_, cell_height_, count_per_row_, count_per_col_, index_;
	const bool m4_;
	map<string, Rect> atlas_;

	int row_ = 0, col_ = 0;

	GLuint texture_ = 0;

	static int image_id_ = 0;
};
