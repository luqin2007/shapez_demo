#include "BuildingMiner.h"

#include "Color.h"
#include "ColoredShapes.h"

BuildingContext BuildingMiner::build_context(const Vec2I& pos, const Side direction) const
{
	return static_cast<BuildingContext>(MinerContext(*this, pos, direction));
}

bool BuildingMiner::can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool BuildingMiner::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool BuildingMiner::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                      const BuildingContext& context) const
{
	return false;
}

void BuildingMiner::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void BuildingMiner::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                  BuildingContext& context) const
{
}

bool BuildingMiner::can_start(TickableContext& context, const GameMap& map) const
{
	return map.get_resource(context.pos) != ResourceType::none;
}

bool BuildingMiner::on_blocking(TickableContext& context, const GameMap& map) const
{
	switch (const ResourceType res = map.get_resource(context.pos))
	{
	case ResourceType::none:
		return true;
	case ResourceType::color_red:
		return send_dye(context.pos, context.direction, Color::red, map);
	case ResourceType::color_blue:
		return send_dye(context.pos, context.direction, Color::blue, map);
	case ResourceType::color_green:
		return send_dye(context.pos, context.direction, Color::green, map);
	default:
		return send_shape(context.pos, context.direction, ColoredShapes::from_resource(res), map);
	}
}

bool BuildingMiner::on_finished(TickableContext& context, const GameMap& map) const
{
	return on_blocking(context, map);
}
