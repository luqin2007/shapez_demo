#pragma once
#include <string>

static std::string color_names[]
{
	"uncolored.png", // 0b000
	"red.png", // 0b001
	"green.png", // 0b010
	"yellow.png", // 0b011
	"blue.png", // 0b100
	"purple.png", // 0b101
	"cyan.png", // 0b110
	"white.png", // 0b111
};

/**
 * \brief 表示颜色
 */
enum class Color
{
	uncolored = 0b000,
	red = 0b001,
	green = 0b010,
	blue = 0b100,
	yellow = 0b011,
	cyan = 0b110,
	purple = 0b101,
	white = 0b111
};

/**
 * \brief 获取颜色名字符串，与纹理材质有关
 * \param color 颜色
 * \return 颜色名
 */
inline std::string& color_icon(const Color color)
{
	return color_names[static_cast<int>(color)];
}

/**
 * \brief 校验两个颜色是否可以混合
 * \param color1 颜色1
 * \param color2 颜色2
 * \return 是否可混合
 */
inline bool operator|(Color color1, Color color2)
{
	return (static_cast<int>(color1) & static_cast<int>(color2)) == 0;
}

/**
 * \brief 获取两个颜色混合后的结果
 * \param color1 颜色1
 * \param color2 颜色2
 * \return 混合后的颜色
 */
inline Color operator+(Color color1, Color color2)
{
	return static_cast<Color>(static_cast<int>(color1) | static_cast<int>(color2));
}
