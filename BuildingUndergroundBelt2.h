#pragma once

#include "TickableBuilding.h"
#include "ColoredShapes.h"
#include "ItemType.h"

class BuildingUndergroundBelt1;
class BuildingUndergroundBelt2;

class UndergroundBelt2Context : public TickableContext
{
	friend BuildingUndergroundBelt1;
	friend BuildingUndergroundBelt2;

public:
	UndergroundBelt2Context(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, FAST)
	{
	}

private:
	ColoredShapes shapes_;
	Color color_ = Color::uncolored;
	ItemType type_ = ItemType::none;
};

/**
 * \brief ´«ËÍÆ÷£¨·¢ËÍ¶Ë£©
 */
class BuildingUndergroundBelt2 final : public TickableBuilding
{
public:
	static const BuildingUndergroundBelt2 instance;

	[[nodiscard]] BuildingContext build_context(const Vec2I& pos, Side direction) const override;
	[[nodiscard]] bool can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const override;
	[[nodiscard]] bool
	can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const override;
	[[nodiscard]] bool can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                                     const BuildingContext& context) const override;
	void receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const override;
	void receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                   BuildingContext& context) const override;

protected:
	BuildingUndergroundBelt2() : TickableBuilding(BuildingSize::small)
	{
	}

	bool can_start(TickableContext& context, const GameMap& map) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;
	bool on_finished(TickableContext& context, const GameMap& map) const override;

	static const UndergroundBelt2Context& cast(const BuildingContext& context)
	{
		return static_cast<const UndergroundBelt2Context&>(context);
	}

	static UndergroundBelt2Context& cast(BuildingContext& context)
	{
		return static_cast<UndergroundBelt2Context&>(context);
	}
};
