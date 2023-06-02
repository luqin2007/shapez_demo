#include "Stacker.h"

#include "StackerRenderer.h"

BuildingContext* Stacker::build_context(const Vec2I& pos, const Side direction) const
{
	return new StackerContext(*this, pos, direction);
}

bool Stacker::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == opposite(context.direction);
}

bool Stacker::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool Stacker::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                const BuildingContext& context) const
{
	if (!can_receive(pos, side, context))
	{
		return false;
	}

	auto& ctx = cast(context);
	return pos == ctx.left_pos_ ? !ctx.is_left_input_ : !ctx.is_right_input_;
}

void Stacker::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void Stacker::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	if (pos == ctx.left_pos_)
	{
		ctx.is_left_input_ = true;
	}
	else
	{
		ctx.is_right_input_ = true;
	}

	if (ctx.shapes_.up_left.second == Shape::none)
	{
		ctx.shapes_.up_left.first = shape.up_left.first;
		ctx.shapes_.up_left.second = shape.up_left.second;
	}
	if (ctx.shapes_.up_right.second == Shape::none)
	{
		ctx.shapes_.up_right.first = shape.up_right.first;
		ctx.shapes_.up_right.second = shape.up_right.second;
	}
	if (ctx.shapes_.down_left.second == Shape::none)
	{
		ctx.shapes_.down_left.first = shape.down_left.first;
		ctx.shapes_.down_left.second = shape.down_left.second;
	}
	if (ctx.shapes_.down_right.second == Shape::none)
	{
		ctx.shapes_.down_right.first = shape.down_right.first;
		ctx.shapes_.down_right.second = shape.down_right.second;
	}
}

void Stacker::free_context(BuildingContext* context) const
{
	delete static_cast<StackerContext*>(context);
}

const BuildingRenderer& Stacker::get_renderer() const
{
	static StackerRenderer renderer;
	return renderer;
}

vector<Vec2I> Stacker::all_positions(const Vec2I& pos, const Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	p.push_back(pos + ~direction);
	return p;
}

bool Stacker::can_start(const TickableContext& context) const
{
	const auto& ctx = cast(context);
	return ctx.is_left_input_ && ctx.is_right_input_;
}

bool Stacker::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		send_shape(ctx.left_pos_, context.direction, ctx.shapes_, map))
	{
		ctx.is_left_input_ = false;
		ctx.is_right_input_ = false;
		ctx.shapes_.up_left.second = Shape::none;
		ctx.shapes_.up_right.second = Shape::none;
		ctx.shapes_.down_left.second = Shape::none;
		ctx.shapes_.down_right.second = Shape::none;
		return true;
	}

	return false;
}
