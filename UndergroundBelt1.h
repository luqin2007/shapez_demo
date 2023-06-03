#pragma once

#include "Building.h"
#include "BuildingContext.h"
#include "ColoredShapes.h"
#include "ItemType.h"

#include "UndergroundBelt2.h"

class UndergroundBelt1;
class UndergroundBelt2;

class UndergroundBelt1Context final : public BuildingContext
{
	friend UndergroundBelt1;
	friend UndergroundBelt2;

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
class UndergroundBelt1 final : public Building
{
public:
	static const UndergroundBelt1& instance()
	{
		static UndergroundBelt1 b;
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
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;
	[[nodiscard]] vector<Vec2I> all_positions(const Vec2I& pos, Side direction) const override;
	void on_placed(BuildingContext& context) const override;

	static const UndergroundBelt1Context& cast(const BuildingContext& context)
	{
		return static_cast<const UndergroundBelt1Context&>(context);
	}

	static UndergroundBelt1Context& cast(BuildingContext& context)
	{
		return static_cast<UndergroundBelt1Context&>(context);
	}
protected:
	UndergroundBelt1()
	{
		next_variant = &UndergroundBelt2::instance();
		const_cast<UndergroundBelt2&>(UndergroundBelt2::instance()).next_variant = this;
	}
};
