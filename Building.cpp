#include "Building.h"

bool Building::can_place(const Vec2I& pos, const Side direction, const GameMap& map) const
{
	Vec2I x0 = pos;
	const Side direction_right = --direction;
	const auto s = size_as_vec(size);
	// 检查每个位置是否有建筑
	for (int i = 0; i < s.x; ++i)
	{
		Vec2I y0 = x0;
		for (int j = 0; j < s.y; ++j)
		{
			if (map.get_building(i, j)) return false;
			y0 = y0 + direction;
		}
		x0 = x0 + direction_right;
	}
	return true;
}

Vec2I Building::size_as_vec(const BuildingSize size)
{
	switch (size)
	{
	case BuildingSize::small: return Vec2I{1, 1};
	case BuildingSize::middle: return Vec2I{1, 2};
	case BuildingSize::large: return Vec2I{1, 3};
	case BuildingSize::special: return Vec2I{4, 4};
	}

	return Vec2I{};
}

vector<Vec2I> Building::all_positions(const Vec2I& pos, const BuildingSize size, const Side direction)
{
	vector<Vec2I> cells;
	const Vec2I size_vec = size_as_vec(size);
	Vec2I x0 = pos;
	for (int i = 0; i < size_vec.x; ++i)
	{
		Vec2I y0 = x0;
		const Side off = ++direction;
		for (int j = 0; j < size_vec.y; ++j)
		{
			cells.push_back(y0);
			y0 = y0 + off;
		}
		x0 = x0 + direction;
	}
	return cells;
}

bool Building::send_dye(const Vec2I& pos, const Side direction, const Color color, const GameMap& map)
{
	const Vec2I target = pos + direction;
	const auto opposite = -direction;
	if (BuildingContext* t_context = map.get_building(target);
		t_context && t_context->building.can_receive_dye(color, target, opposite, *t_context))
	{
		// 发送
		t_context->building.receive_dye(color, target, opposite, *t_context);
		return true;
	}

	return false;
}

bool Building::send_shape(const Vec2I& pos, const Side direction, const ColoredShapes& shape, const GameMap& map)
{
	const Vec2I target = pos + direction;
	const auto opposite = -direction;
	if (BuildingContext* t_context = map.get_building(target);
		t_context && t_context->building.can_receive_shape(shape, target, opposite, *t_context))
	{
		// 发送
		t_context->building.receive_shape(shape, target, opposite, *t_context);
		return true;
	}

	return false;
}
