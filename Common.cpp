#include "Common.h"

Side operator++(Side side)
{
	switch (side)
	{
	case Side::UP: return Side::RIGHT;
	case Side::RIGHT: return Side::DOWN;
	case Side::DOWN: return Side::LEFT;
	default: return Side::UP;
	}
}

Side operator--(Side side)
{
	switch (side)
	{
	case Side::UP: return Side::LEFT;
	case Side::LEFT: return Side::DOWN;
	case Side::DOWN: return Side::RIGHT;
	default: return Side::UP;
	}
}

Side operator-(Side side)
{
	switch (side)
	{
	case Side::UP: return Side::DOWN;
	case Side::DOWN: return Side::UP;
	case Side::LEFT: return Side::RIGHT;
	default: return Side::LEFT;
	}
}

ivec2 operator+(const ivec2& pos, Side side)
{
	switch (side)
	{
	case Side::UP:
		return ivec2{pos.x, pos.y + 1};
	case Side::DOWN:
		return ivec2{pos.x, pos.y - 1};
	case Side::LEFT:
		return ivec2{pos.x - 1, pos.y};
	case Side::RIGHT:
		return ivec2{pos.x + 1, pos.y};
	default:
		return ivec2{pos};
	}
}

Color* _colors[10];

Color::Color(std::string _name, const int _mix) : name(std::move(_name)), mix(_mix)
{
	_colors[_mix] = this;
}

const Color Color::uncolored{"uncolored", 0b000};
const Color Color::red{"red", 0b001};
const Color Color::green{"green", 0b010};
const Color Color::blue{"blue", 0b100};
const Color Color::yellow{"yellow", 0b011};
const Color Color::cyan{"cyan", 0b110};
const Color Color::purple{"purple", 0b101};
const Color Color::white{"white", 0b111};

const Color& Color::operator+(const Color& o) const
{
	return *_colors[mix | o.mix];
}

bool Color::operator==(const Color& o) const
{
	return mix == o.mix;
}
