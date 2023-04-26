#pragma once

#include <string>

struct ivec2
{
	int x{0};
	int y{0};

	ivec2() = default;

	ivec2(int x, int y)
		: x(x), y(y)
	{
	}
};

struct vec2
{
	float x{0};
	float y{0};

	vec2() = default;

	vec2(float x, float y)
		: x(x), y(y)
	{
	}
};

enum class Side
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

/**
 * 顺时针旋转
 */
Side operator++(Side side);

/**
 * 逆时针旋转
 */
Side operator--(Side side);

/**
 * 反方向
 */
Side operator-(Side side);

/**
 * 向某一方向移动一单位
 */
ivec2 operator+(const ivec2& pos, Side side);

/**
 * 颜色 模拟枚举
 */
class Color
{
public:
	const std::string name;
	const int mix;

	const static Color uncolored;
	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color yellow;
	const static Color cyan;
	const static Color purple;
	const static Color white;

	const Color& operator+(const Color& o) const;

	bool operator==(const Color& o) const;

private:
	Color(std::string _name, int _mix);
};
