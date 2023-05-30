#pragma once

#include "TickableBuilding.h"
#include "ColoredShapes.h"
#include "ItemType.h"

class UndergroundBelt1;
class UndergroundBelt2;

class UndergroundBelt2Context final : public TickableContext
{
	friend UndergroundBelt1;
	friend UndergroundBelt2;

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
 * \brief 传送器（发送端）
 */
class UndergroundBelt2 final : public TickableBuilding
{
public:
	static const UndergroundBelt2& instance()
	{
		static UndergroundBelt2 b;
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
	void free_context(BuildingContext* context) const override;
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;
	[[nodiscard]] vector<Vec2I> all_positions(const Vec2I& pos, Side direction) const override;

protected:
	UndergroundBelt2() = default;

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
