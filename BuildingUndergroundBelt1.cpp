#include "BuildingUndergroundBelt1.h"

#include "GameLogic.h"

BuildingContext* BuildingUndergroundBelt1::build_context(const Vec2I& pos, const Side direction) const
{
	return new UndergroundBelt1Context{*this, pos, direction};
}

bool BuildingUndergroundBelt1::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingUndergroundBelt1::can_receive_dye(Color color, const Vec2I& pos, Side side,
                                               const BuildingContext& context) const
{
	return cast(context).type_ == ItemType::none;
}

bool BuildingUndergroundBelt1::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                                 const BuildingContext& context) const
{
	return cast(context).type_ == ItemType::none;
}

void BuildingUndergroundBelt1::receive_dye(const Color color, const Vec2I& pos, Side side,
                                           BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.type_ = ItemType::dye;
	ctx.color_ = color;
}

void BuildingUndergroundBelt1::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                             BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.type_ = ItemType::shape;
	ctx.shapes_ = shape;
}

void BuildingUndergroundBelt1::update(BuildingContext& context, GameMap& map) const
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

	const auto* building = dynamic_cast<const BuildingUndergroundBelt2*>(&target->building);
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

void BuildingUndergroundBelt1::free_context(BuildingContext* context) const
{
	delete static_cast<UndergroundBelt1Context*>(context);
}
