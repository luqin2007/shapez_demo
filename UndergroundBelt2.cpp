#include "UndergroundBelt2.h"

#include "ItemType.h"
#include "UndergroundBelt2Renderer.h"

BuildingContext* UndergroundBelt2::build_context(const Vec2I& pos, const Side direction) const
{
	return new UndergroundBelt2Context{*this, pos, direction};
}

bool UndergroundBelt2::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == opposite(context.direction);
}

bool UndergroundBelt2::can_receive_dye(Color color, const Vec2I& pos, const Side side,
                                               const BuildingContext& context) const
{
	return can_receive(pos, side, context) && cast(context).type_ == ItemType::none;
}

bool UndergroundBelt2::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                                 const BuildingContext& context) const
{
	return can_receive(pos, side, context) && cast(context).type_ == ItemType::none;
}

void UndergroundBelt2::receive_dye(const Color color, const Vec2I& pos, Side side,
                                           BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.color_ = color;
	ctx.type_ = ItemType::dye;
}

void UndergroundBelt2::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                             BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.shapes_ = shape;
	ctx.type_ = ItemType::shape;
}

void UndergroundBelt2::free_context(BuildingContext* context) const
{
	delete static_cast<UndergroundBelt2Context*>(context);
}

const BuildingRenderer& UndergroundBelt2::get_renderer() const
{
	static UndergroundBelt2Renderer renderer;
	return renderer;
}

vector<Vec2I> UndergroundBelt2::all_positions(const Vec2I& pos, Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	return p;
}

bool UndergroundBelt2::can_start(const TickableContext& context) const
{
	return cast(context).type_ != ItemType::none;
}

bool UndergroundBelt2::on_blocking(TickableContext& context, const GameMap& map) const
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
