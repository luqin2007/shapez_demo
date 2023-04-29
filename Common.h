#pragma once

#include <string>
#include <cmath>
#include <iostream>
#include <exception>
#include <glad/glad.h>

class GameWindow;
class GameRenderer;
class GameLogic;

extern GameLogic* current_game;
extern GameWindow* current_window;
extern GameRenderer* current_renderer;

using std::fabsf;
using std::cerr;
using std::cout;
using std::endl;
using std::exception;

struct ivec2
{
	union
	{
		int x{0};
		int w;
	};

	union
	{
		int y{0};
		int h;
	};

	ivec2() = default;

	ivec2(const int x, const int y): x(x), y(y)
	{
	}
};

struct vec2
{
	union
	{
		float x{0};
		float w;
	};

	union
	{
		float y{0};
		float h;
	};

	vec2() = default;

	vec2(const float x, const float y): x(x), y(y)
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
 * 反向
 */
Side operator-(Side side);

/**
 * 移动
 */
ivec2 operator+(const ivec2& pos, Side side);

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
	Color(std::string name, int mix);
};

inline bool fneq(float a, float b)
{
	return fabsf(a - b) > 1e-5f;
}

void log_error(const char* name);

template<typename T>
void debug_buffer(GLuint name, int count);