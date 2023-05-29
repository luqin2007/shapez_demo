#include "BuildingStacker.h"

BuildingContext* BuildingStacker::build_context(const Vec2I& pos, const Side direction) const
{
	return new StackerContext(*this, pos, direction);
}

bool BuildingStacker::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingStacker::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool BuildingStacker::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                        const BuildingContext& context) const
{
	if (!can_receive(pos, side, context))
	{
		return false;
	}

	auto& ctx = cast(context);
	if (pos == context.pos && ctx.is_left_input_)
	{
		return false;
	}
	if (pos != context.pos && ctx.is_right_input_)
	{
		return false;
	}

	if (ctx.shapes_.up_left.second != Shape::none && shape.up_left.second != Shape::none)
	{
		return false;
	}
	if (ctx.shapes_.up_right.second != Shape::none && shape.up_right.second != Shape::none)
	{
		return false;
	}
	if (ctx.shapes_.down_left.second != Shape::none && shape.down_left.second != Shape::none)
	{
		return false;
	}
	if (ctx.shapes_.down_right.second != Shape::none && shape.down_right.second != Shape::none)
	{
		return false;
	}

	return true;
}

void BuildingStacker::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void BuildingStacker::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                    BuildingContext& context) const
{
}

void BuildingStacker::free_context(BuildingContext* context) const
{
	delete static_cast<StackerContext*>(context);
}

bool BuildingStacker::can_start(TickableContext& context, const GameMap& map) const
{
	const auto& ctx = cast(context);
	return ctx.is_left_input_ && ctx.is_right_input_;
}

bool BuildingStacker::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		send_shape(context.pos, context.direction, ctx.shapes_, map))
	{
		ctx.is_left_input_ = false;
		ctx.is_right_input_ = false;
		return true;
	}

	return false;
}

bool BuildingStacker::on_finished(TickableContext& context, const GameMap& map) const
{
	return on_blocking(context, map);
}
