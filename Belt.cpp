#include "Belt.h"

#include "BeltRenderer.h"

bool Belt::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool Belt::can_receive_dye(Color color, const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	const BeltContext& ctx = cast(context);
	return side == -context.direction && ctx.item_count_ != 2
		&& (ctx.item_count_ == 0 || ctx.item_pos_[ctx.first_] >= 0.5f);
}

bool Belt::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                             const BuildingContext& context) const
{
	const BeltContext& ctx = cast(context);
	return side == -context.direction && ctx.item_count_ != 2
		&& (ctx.item_count_ == 0 || ctx.item_pos_[ctx.first_] >= 0.5f);
}

void Belt::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	if (auto& ctx = cast(context); ctx.item_count_ == 0)
	{
		ctx.item_types_[ctx.first_] = ItemType::dye;
		ctx.item_pos_[ctx.first_] = 0;
		ctx.dyes_[ctx.first_] = color;
		ctx.item_count_ = 1;
	}
	else if (ctx.item_count_ == 1)
	{
		ctx.item_types_[ctx.second_] = ItemType::dye;
		ctx.item_pos_[ctx.second_] = 0;
		ctx.dyes_[ctx.second_] = color;
		ctx.item_count_ = 2;
	}
}

void Belt::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side, BuildingContext& context) const
{
	if (auto& ctx = cast(context); ctx.item_count_ == 0)
	{
		ctx.item_types_[ctx.first_] = ItemType::shape;
		ctx.item_pos_[ctx.first_] = 0;
		ctx.shapes_[ctx.first_] = shape;
		ctx.item_count_ = 1;
	}
	else if (ctx.item_count_ == 1)
	{
		ctx.item_types_[ctx.second_] = ItemType::shape;
		ctx.item_pos_[ctx.second_] = 0;
		ctx.shapes_[ctx.second_] = shape;
		ctx.item_count_ = 2;
	}
}

void Belt::update(BuildingContext& context, GameMap& map) const
{
	auto& ctx = cast(context);

	const float ss = ctx.speed_ * current_game->timer().delta;
	if (ctx.item_count_ && ctx.item_pos_[ctx.first_] < 1.0000001f)
	{
		ctx.item_pos_[ctx.first_] += ss;
	}
	if (ctx.item_count_ == 2 && ctx.item_pos_[ctx.second_] < 0.5000001f)
	{
		ctx.item_pos_[ctx.second_] += ss;
	}

	if (ctx.item_pos_[ctx.first_] > 0.99999999f)
	{
		// 可输出
		bool send = false;
		if (ctx.item_types_[ctx.first_] == ItemType::dye)
		{
			send = send_dye(context.pos, ctx.output_, ctx.dyes_[ctx.first_], map);
		}
		else if (ctx.item_types_[ctx.first_] == ItemType::shape)
		{
			send = send_shape(context.pos, ctx.output_, ctx.shapes_[ctx.first_], map);
		}
		if (send)
		{
			// 迁移
			std::swap(ctx.first_, ctx.second_);
			if (ctx.item_pos_[ctx.first_] > 0.5000001f)
			{
				ctx.item_pos_[ctx.first_] = 0.5000001f;
			}
			ctx.item_count_--;
		}
	}
}

void Belt::free_context(BuildingContext* context) const
{
	delete static_cast<BeltContext*>(context);
}

vector<Vec2I> Belt::all_positions(const Vec2I& pos, Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	return p;
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
