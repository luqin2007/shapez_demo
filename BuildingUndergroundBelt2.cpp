#include "BuildingUndergroundBelt2.h"

#include "ItemType.h"

BuildingContext BuildingUndergroundBelt2::build_context(const Vec2I& pos, const Side direction) const
{
	return static_cast<BuildingContext>(UndergroundBelt2Context{*this, pos, direction});
}

bool BuildingUndergroundBelt2::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingUndergroundBelt2::can_receive_dye(Color color, const Vec2I& pos, const Side side,
                                               const BuildingContext& context) const
{
	return can_receive(pos, side, context) && cast(context).type_ == ItemType::none;
}

bool BuildingUndergroundBelt2::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                                 const BuildingContext& context) const
{
	return can_receive(pos, side, context) && cast(context).type_ == ItemType::none;
}

void BuildingUndergroundBelt2::receive_dye(const Color color, const Vec2I& pos, Side side,
                                           BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.color_ = color;
	ctx.type_ = ItemType::dye;
}

void BuildingUndergroundBelt2::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                             BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.shapes_ = shape;
	ctx.type_ = ItemType::shape;
}

bool BuildingUndergroundBelt2::can_start(TickableContext& context, const GameMap& map) const
{
	return cast(context).type_ != ItemType::none;
}

bool BuildingUndergroundBelt2::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (const auto& ctx = cast(context);
		ctx.type_ == ItemType::dye)
	{
		return send_dye(context.pos, context.direction, cast(context).color_, map);
	}
	else if (ctx.type_ == ItemType::shape)
	{
		return send_shape(context.pos, context.direction, cast(context).shapes_, map);
	}

	return true;
}

bool BuildingUndergroundBelt2::on_finished(TickableContext& context, const GameMap& map) const
{
	return on_blocking(context, map);
}
