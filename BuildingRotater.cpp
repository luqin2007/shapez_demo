#include "BuildingRotater.h"

#include "ColoredShapes.h"

BuildingContext BuildingRotater::build_context(const Vec2I& pos, const Side direction) const
{
	return static_cast<BuildingContext>(RotaterContext(*this, pos, direction));
}

bool BuildingRotater::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingRotater::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool BuildingRotater::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                        const BuildingContext& context) const
{
	return !cast(context).has_shape_ && side == -context.direction;
}

void BuildingRotater::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void BuildingRotater::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                    BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_shape_ = true;
	ctx.shapes_ = shape;
}

bool BuildingRotater::can_start(TickableContext& context, const GameMap& map) const
{
	return cast(context).has_shape_;
}

bool BuildingRotater::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (send_shape(context.pos, context.direction, cast(context).shapes_, map))
	{
		cast(context).has_shape_ = false;
		return true;
	}
	return false;
}

bool BuildingRotater::on_finished(TickableContext& context, const GameMap& map) const
{
	return on_blocking(context, map);
}
