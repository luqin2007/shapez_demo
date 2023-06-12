#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <exception>

#include <glad/glad.h>

using std::unordered_map;
using std::string;
using std::filesystem::path;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

class TextureDrawer;
class FontDrawer;

/**
 * \brief 表示地图集中的一个图片
 */
struct Rect
{
	float u, v, w, h;
};

/**
 * \brief .9 图配置
 */
struct dot9
{
	float up, down, left, right;

	dot9() = default;

	dot9(const float left, const float right, const float up, const float down):
		up(up), down(down), left(left), right(right)
	{
	}

	dot9(const float x, const float y): up(y), down(y), left(x), right(x)
	{
	}
};

/**
 * \brief 字体
 */
struct Char
{
	unsigned int width, height; // 字形大大小
	int bearing_x, bearing_y; // 字形基于基线和起点的位置
	GLuint advance; // 起点到下一个字形起点的距离
};

enum class Action
{
	/**
	 * \brief 将给定图片划分为 4 份分别储存
	 */
	m4,
	/**
	 * \brief 生成 Mipmap
	 */
	mipmap,
	/**
	 * \brief 图片存储完成
	 */
	finished
};

/**
 * \brief 地图集，将多张图片集合到一张图中，每张图片的长宽应与给定单元长度的倍数相同或相近以最大限度利用空间
 */
class Atlas
{
	friend TextureDrawer;
	friend FontDrawer;

public:
	/**
	 * \brief 地图集
	 * \param width 地图集宽度
	 * \param height 地图集高度
	 * \param cell_width 每个单元宽度
	 * \param cell_height 每个单元高度
	 */
	Atlas(float width, float height, int cell_width, int cell_height);

	/**
	 * \brief 初始化
	 */
	Atlas& initialize();

	/**
	 * \brief 销毁
	 */
	void destroy() const;

	/**
	 * \brief 向地图集中导入图片，应当在 initialize 方法之后调用
	 * \param p 图片完整路径
	 * \return 当前地图集
	 */
	Atlas& operator<<(const path& p);

	/**
	 * \brief 控制地图集
	 * \param action 控制行为
	 * \return 当前地图集
	 */
	Atlas& operator<<(Action action);

	/**
	 * \brief 导入 .9 图
	 * \data 上下左右偏移量
	 * \return 当前地图集
	 */
	Atlas& operator<<(dot9 data);

	/**
	 * \brief 导入文本
	 * \param text 待存文本
	 * \return 当前地图集
	 */
	Atlas& operator<<(const char* text);

	Rect& operator[](const string& name);

	Rect& operator[](const char* name);

private:
	inline static int image_id_ = 0;

	const float width_, height_;
	const int cell_width_, cell_height_, col_count_, row_count_, index_;
	bool m4_ = false;
	unordered_map<string, Rect> atlas_;
	unordered_map<string, dot9> dot9s_;
	unordered_map<char, Char> chars_;

	GLuint texture_ = 0;

	bool** is_space_used_ = nullptr;
	int best_cell_width_ = 0, best_cell_height_ = 0;

	bool has_d9_ = false;
	dot9 d9_{0, 0, 0, 0};

	int bcd(int a, int b);

	void put_image(int width, int height, GLenum format, const char* name, const void* image);
};
