#pragma once

#include "Building.h"
#include "BuildingContext.h"
#include "ColoredShapes.h"
#include "ItemType.h"

#include "BuildingUndergroundBelt2.h"

class BuildingUndergroundBelt1;

class UndergroundBelt1Context : public BuildingContext
{
	friend BuildingUndergroundBelt1;

public:
	UndergroundBelt1Context(const Building& building, const Vec2I& pos, const Side direction)
		: BuildingContext(building, pos, direction)
	{
	}

private:
	Color color_;
	ColoredShapes shapes_;
	ItemType type_ = ItemType::none;

	Vec2I target_{0, 0};
};

/**
 * \brief 传送器（输入端）
 */
class BuildingUndergroundBelt1 final : public Building
{
public:
	static const BuildingUndergroundBelt1& instance()
	{
		static BuildingUndergroundBelt1 b;
		return b;
	}

	[[nodiscard]] BuildingContext* build_context(const Vec2I& pos, Side direction) const override;
	[[nodiscard]] bool can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const override;
	[[nodiscard]] bool
	can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const override;
	[[nodiscard]] bool can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                                     const BuildingContext& context) const override;
	void receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const override;
	void receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                   BuildingContext& context) const override;
	void update(BuildingContext& context, GameMap& map) const override;
	void free_context(BuildingContext* context) const override;

protected:
	BuildingUndergroundBelt1() : Building(BuildingSize::small, "underground_belt.png", "underground_belt_entry.png",
	                                      "underground_belt_entry_blue.png")
	{
		next_variant = &BuildingUndergroundBelt2::instance();
		const_cast<BuildingUndergroundBelt2&>(BuildingUndergroundBelt2::instance()).next_variant = this;
	}

	static const UndergroundBelt1Context& cast(const BuildingContext& context)
	{
		return static_cast<const UndergroundBelt1Context&>(context);
	}

	static UndergroundBelt1Context& cast(BuildingContext& context)
	{
		return static_cast<UndergroundBelt1Context&>(context);
	}
};
