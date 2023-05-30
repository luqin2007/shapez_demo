#include "Belt.h"

#include "BeltRenderer.h"

bool Belt::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool Belt::can_receive_dye(Color color, const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	const BeltContext& ctx = cast(context);
	return can_receive(pos, side, context) && ctx.p_item_ != 3 && ctx.item_pos[ctx.p_item_] > ctx.max_pos_[1];
}

bool Belt::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                     const BuildingContext& context) const
{
	const BeltContext& ctx = cast(context);
	return can_receive(pos, side, context) && ctx.p_item_ != 3 && ctx.item_pos[ctx.p_item_] > ctx.max_pos_[1];
}

void Belt::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.types[ctx.p_item_] = ItemType::dye;
	ctx.indices[ctx.p_item_] = ctx.p_dye;
	ctx.item_pos[ctx.p_item_] = 0;
	ctx.dyes[ctx.p_dye] = color;
	ctx.p_dye = (ctx.p_dye + 1) % 4;
	ctx.p_item_--;
}

void Belt::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                 BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.types[ctx.p_item_] = ItemType::shape;
	ctx.indices[ctx.p_item_] = ctx.p_shape;
	ctx.item_pos[ctx.p_item_] = 0;
	ctx.shapes[ctx.p_shape] = shape;
	ctx.p_shape = (ctx.p_shape + 1) % 4;
	ctx.p_item_--;
}

void Belt::update(BuildingContext& context, GameMap& map) const
{
	auto& ctx = cast(context);

	const float ss = ctx.speed_ * current_game->timer().delta;
	for (int i = 1; i <= ctx.p_item_; ++i)
	{
		ctx.item_pos[i] += ss;
		if (ctx.item_pos[i] > ctx.max_pos_[i])
		{
			ctx.item_pos[i] = ctx.max_pos_[i];
		}
	}

	// 可输出
	bool send = false;
	if (ctx.types[3] == ItemType::dye)
	{
		send = send_dye(context.pos, ctx.output_, ctx.dyes[ctx.indices[3]], map);
	}
	else if (ctx.types[3] == ItemType::shape)
	{
		send = send_shape(context.pos, ctx.output_, ctx.shapes[ctx.indices[3]], map);
	}
	if (send)
	{
		// 迁移
		ctx.types[3] = ctx.types[2];
		ctx.types[2] = ctx.types[1];
		ctx.types[1] = ctx.types[0];

		ctx.indices[3] = ctx.indices[2];
		ctx.indices[2] = ctx.indices[1];
		ctx.indices[1] = ctx.indices[0];

		ctx.item_pos[3] = ctx.item_pos[2];
		ctx.item_pos[2] = ctx.item_pos[1];
		ctx.item_pos[1] = ctx.item_pos[0];

		ctx.p_item_++;
	}
}

void Belt::free_context(BuildingContext* context) const
{
	delete static_cast<BeltContext*>(context);
}

vector<Vec2I> Belt::all_positions(const Vec2I& pos, Side direction) const
{
	return pos_small(pos);
}

BuildingContext* BeltDirect::build_context(const Vec2I& pos, const Side direction) const
{
	return new BeltContext(*this, pos, direction, direction);
}

const BuildingRenderer& BeltDirect::get_renderer() const
{
	static BeltDirectRenderer renderer;
	return renderer;
}

BuildingContext* BeltLeft::build_context(const Vec2I& pos, const Side direction) const
{
	return new BeltContext(*this, pos, direction, --direction);
}

const BuildingRenderer& BeltLeft::get_renderer() const
{
	static BeltLeftRenderer renderer;
	return renderer;
}

BuildingContext* BeltRight::build_context(const Vec2I& pos, const Side direction) const
{
	return new BeltContext(*this, pos, direction, ++direction);
}

const BuildingRenderer& BeltRight::get_renderer() const
{
	static BeltRightRenderer renderer;
	return renderer;
}

const Belt& Belts::direct()
{
	static BeltDirect d;
	static BeltLeft l;
	static BeltRight r;

	d.next_variant = &l;
	l.next_variant = &r;
	r.next_variant = &d;
	return d;
}

const Belt& Belts::left()
{
	return *dynamic_cast<const Belt*>(direct().next_variant);
}

const Belt& Belts::right()
{
	return *dynamic_cast<const Belt*>(left().next_variant);
}
