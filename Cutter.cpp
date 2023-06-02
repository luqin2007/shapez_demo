#include "Cutter.h"

#include "ColoredShapes.h"
#include "CutterRenderer.h"

class Item;

BuildingContext* Cutter::build_context(const Vec2I& pos, const Side direction) const
{
	return new CutterContext(*this, pos, direction);
}

bool Cutter::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == opposite(context.direction) && pos == cast(context).left_pos_;
}

bool Cutter::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool Cutter::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                               const BuildingContext& context) const
{
	return can_receive(pos, side, context) && !cast(context).has_shape_;
}

void Cutter::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void Cutter::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                           BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.left_ = shape.left();
	ctx.right_ = shape.right();
	ctx.has_left_ = ctx.has_right_ = ctx.has_shape_ = true;
}

void Cutter::free_context(BuildingContext* context) const
{
	delete static_cast<CutterContext*>(context);
}

const BuildingRenderer& Cutter::get_renderer() const
{
	static CutterRenderer renderer;
	return renderer;
}

vector<Vec2I> Cutter::all_positions(const Vec2I& pos, const Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	p.push_back(pos + ~direction);
	return p;
}

bool Cutter::can_start(const TickableContext& context) const
{
	return cast(context).has_shape_;
}

bool Cutter::on_blocking(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);

	if (ctx.has_left_)
	{
		ctx.has_left_ = !send_shape(ctx.left_pos_, context.direction, ctx.left_, map);
	}

	if (ctx.has_right_)
	{
		ctx.has_right_ = !send_shape(ctx.right_pos_, context.direction, ctx.right_, map);
	}
	ctx.has_shape_ = ctx.has_left_ || ctx.has_right_;
	return !ctx.has_shape_;
}
