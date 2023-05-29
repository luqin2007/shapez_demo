#pragma once

#include "math.h"
#include "Side.h"

struct Vec2I
{
	union
	{
		int x;
		int w{};
	};

	union
	{
		int y;
		int h{};
	};

	explicit Vec2I(const int x = 0, const int y = 0) : x(x), y(y)
	{
	}

	Vec2I operator+(const Side side) const
	{
		switch (side)
		{
		case Side::up:
			return Vec2I{ x - 1, y };
		case Side::down:
			return Vec2I{ x + 1, y };
		case Side::left:
			return Vec2I{ x, y - 1 };
		case Side::right:
			return Vec2I{ x, y + 1 };
		}
		return Vec2I{ x, y };
	}

	bool operator==(const Vec2I& pos) const
	{
		return x == pos.x && y == pos.y;
	}
};

struct Vec2
{
	union
	{
		float x;
		float w{};
	};

	union
	{
		float y;
		float h{};
	};

	explicit Vec2(const float x = 0, const float y = 0) : x(x), y(y)
	{
	}

	bool operator==(const Vec2& o) const
	{
		return feq(x, o.x) && feq(y, o.y);
	}
};
