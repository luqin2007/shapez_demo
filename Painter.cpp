#include "Painter.h"

#include "PainterRenderer.h"

BuildingContext* Painter::build_context(const Vec2I& pos, const Side direction) const
{
	return new PainterContext(*this, pos, direction);
}

bool Painter::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	const auto& ctx = cast(context);
	return pos == ctx.left_pos_ ? side == cw(context.direction): side == opposite(context.direction);
}

bool Painter::can_receive_dye(const Color color, const Vec2I& pos, const Side side,
                              const BuildingContext& context) const
{
	const auto& ctx = cast(context);
	return !ctx.has_color_ && pos == ctx.right_pos_ && side == context.direction
		&& (!ctx.has_shape_ || ctx.shapes_ | color);
}

bool Painter::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                const BuildingContext& context) const
{
	const auto& ctx = cast(context);
	return !ctx.has_shape_ && pos == ctx.left_pos_ && side == ccw(context.direction)
		&& (!ctx.has_color_ || shape | ctx.color_);
}

void Painter::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_color_ = true;
	ctx.color_ = color;

	if (ctx.has_shape_)
	{
		ctx.shapes_.up_left.first = ctx.shapes_.up_left.first + ctx.color_;
		ctx.shapes_.up_right.first = ctx.shapes_.up_right.first + ctx.color_;
		ctx.shapes_.down_left.first = ctx.shapes_.down_left.first + ctx.color_;
		ctx.shapes_.down_right.first = ctx.shapes_.down_right.first + ctx.color_;
	}
}

void Painter::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_shape_ = true;
	ctx.shapes_ = shape;

	if (ctx.has_color_)
	{
		ctx.shapes_.up_left.first = ctx.shapes_.up_left.first + ctx.color_;
		ctx.shapes_.up_right.first = ctx.shapes_.up_right.first + ctx.color_;
		ctx.shapes_.down_left.first = ctx.shapes_.down_left.first + ctx.color_;
		ctx.shapes_.down_right.first = ctx.shapes_.down_right.first + ctx.color_;
	}
}

void Painter::free_context(BuildingContext* context) const
{
	delete static_cast<PainterContext*>(context);
}

const BuildingRenderer& Painter::get_renderer() const
{
	static PainterRenderer renderer;
	return renderer;
}

vector<Vec2I> Painter::all_positions(const Vec2I& pos, const Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	p.push_back(pos + ~direction);
	return p;
}

bool Painter::can_start(const TickableContext& context) const
{
	const auto& ctx = cast(context);
	return ctx.has_color_ && ctx.has_shape_;
}

bool Painter::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		send_shape(ctx.right_pos_, cw(context.direction), ctx.shapes_, map))
	{
		ctx.has_color_ = false;
		ctx.has_shape_ = false;
		return true;
	}
	return false;
}
