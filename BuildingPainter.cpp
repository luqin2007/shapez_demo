#include "BuildingPainter.h"

BuildingContext BuildingPainter::build_context(const Vec2I& pos, Side direction) const
{
	return static_cast<BuildingContext>(PainterContext(*this, pos, direction));
}

bool BuildingPainter::can_receive_dye(Color color, const Vec2I& pos, const Side side,
                                      const BuildingContext& context) const
{
	const auto& ctx = cast(context);
	return pos == context.pos + ++context.direction && side == context.direction && !ctx.has_color_ && (!ctx.has_shape_
		|| ctx.shapes_ | color);
}

bool BuildingPainter::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                        const BuildingContext& context) const
{
	const auto& ctx = cast(context);
	return pos == context.pos && side == --context.direction && !ctx.has_shape_ && (!ctx.has_color_ || shape | ctx.
		color_);
}

void BuildingPainter::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_color_ = true;
	ctx.color_ = color;
}

void BuildingPainter::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                    BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_shape_ = true;
	ctx.shapes_ = shape;
}

bool BuildingPainter::can_start(TickableContext& context, const GameMap& map) const
{
	const auto& ctx = cast(context);
	return ctx.has_color_ && ctx.has_shape_;
}

bool BuildingPainter::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		send_shape(context.pos + ++context.direction, ++context.direction, ctx.shapes_, map))
	{
		ctx.has_color_ = false;
		ctx.has_shape_ = false;
		return true;
	}
	return false;
}

bool BuildingPainter::on_finished(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);
	ctx.shapes_.up_left.first = ctx.shapes_.up_left.first + ctx.color_;
	ctx.shapes_.up_right.first = ctx.shapes_.up_right.first + ctx.color_;
	ctx.shapes_.down_left.first = ctx.shapes_.down_left.first + ctx.color_;
	ctx.shapes_.down_right.first = ctx.shapes_.down_right.first + ctx.color_;
	return on_blocking(context, map);
}
