#include "UndergroundBelt1.h"

#include "GameLogic.h"
#include "UndergroundBelt1Renderer.h"

BuildingContext* UndergroundBelt1::build_context(const Vec2I& pos, const Side direction) const
{
	return new UndergroundBelt1Context{*this, pos, direction};
}

bool UndergroundBelt1::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool UndergroundBelt1::can_receive_dye(Color color, const Vec2I& pos, Side side,
                                               const BuildingContext& context) const
{
	return cast(context).type_ == ItemType::none;
}

bool UndergroundBelt1::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                                 const BuildingContext& context) const
{
	return cast(context).type_ == ItemType::none;
}

void UndergroundBelt1::receive_dye(const Color color, const Vec2I& pos, Side side,
                                           BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.type_ = ItemType::dye;
	ctx.color_ = color;
}

void UndergroundBelt1::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                             BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.type_ = ItemType::shape;
	ctx.shapes_ = shape;
}

void UndergroundBelt1::update(BuildingContext& context, GameMap& map) const
{
	const auto& ctx = cast(context);
	if (ctx.type_ == ItemType::none)
	{
		return;
	}

	BuildingContext* target = map.get_building(ctx.target_);
	if (!target)
	{
		return;
	}

	const auto* building = dynamic_cast<const UndergroundBelt2*>(&target->building);
	if (!building)
	{
		return;
	}

	if (ctx.type_ == ItemType::dye)
	{
		if (building->can_receive_dye(ctx.color_, context.pos, -context.direction, *target))
		{
			building->receive_dye(ctx.color_, context.pos, -context.direction, *target);
		}
	}
	else
	{
		if (building->can_receive_shape(ctx.shapes_, context.pos, -context.direction, *target))
		{
			building->receive_shape(ctx.shapes_, context.pos, -context.direction, *target);
		}
	}
}

void UndergroundBelt1::free_context(BuildingContext* context) const
{
	delete static_cast<UndergroundBelt1Context*>(context);
}

const BuildingRenderer& UndergroundBelt1::get_renderer() const
{
	static UndergroundBelt1Renderer renderer;
	return renderer;
}

vector<Vec2I> UndergroundBelt1::all_positions(const Vec2I& pos, Side direction) const
{
	return pos_small(pos);
}
