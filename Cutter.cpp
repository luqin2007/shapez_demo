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
	return pos == context.pos && side == -context.direction;
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
	ctx.has_shape_ = true;
	ctx.shapes_ = shape;
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
	return pos_middle(pos, direction);
}

bool Cutter::can_start(TickableContext& context, const GameMap& map) const
{
	return cast(context).has_shape_;
}

bool Cutter::on_blocking(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);

	if (ctx.has_left_)
	{
		ctx.has_left_ = !send_shape(context.pos, context.direction, {
			                            {Color::uncolored, Shape::none},
			                            ctx.shapes_.down_left,
			                            {Color::uncolored, Shape::none},
			                            ctx.shapes_.up_left,
		                            }, map);
	}

	if (ctx.has_right_)
	{
		ctx.has_right_ = !send_shape(context.pos, context.direction, {
			                             ctx.shapes_.down_right,
			                             {Color::uncolored, Shape::none},
			                             ctx.shapes_.up_right,
			                             {Color::uncolored, Shape::none},
		                             }, map);
	}

	ctx.has_shape_ = ctx.has_left_ || ctx.has_right_;
	return !ctx.has_shape_;
}

bool Cutter::on_finished(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);
	ctx.has_left_ = ctx.shapes_.up_left.second != Shape::none || ctx.shapes_.down_left.second != Shape::none;
	ctx.has_right_ = ctx.shapes_.up_right.second != Shape::none || ctx.shapes_.down_right.second != Shape::none;
	return on_blocking(context, map);
}

void Cutter::send_shape_items(CutterContext& context, const GameMap& map)
{
}