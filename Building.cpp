#include "Building.h"

bool Building::can_place(const Vec2I& pos, const Side direction, const GameMap& map) const
{
	// 检查每个位置是否有建筑
	for (const auto& position : all_positions(pos, direction))
	{
		if (map.get_building(position)) return false;
	}
	return true;
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

vector<Vec2I> Building::pos_small(const Vec2I& pos)
{
	vector<Vec2I> p;
	p.push_back(pos);
	return p;
}

vector<Vec2I> Building::pos_middle(const Vec2I& pos, const Side direction)
{
	vector<Vec2I> p;
	p.push_back(pos);
	p.push_back(pos + ++direction);
	return p;
}

vector<Vec2I> Building::pos_large(const Vec2I& pos, const Side direction)
{
	vector<Vec2I> p;
	const Side d = ++direction;
	p.push_back(pos);
	p.push_back(pos + d);
	p.push_back(pos + d + d);
	return p;
}

vector<Vec2I> Building::pos_special(const Vec2I& pos)
{
	vector<Vec2I> p;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			p.emplace_back(pos.x + i, pos.y + j);
		}
	}
	return p;
}
