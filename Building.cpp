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
