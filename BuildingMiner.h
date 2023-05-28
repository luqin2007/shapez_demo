#pragma once

#include "TickableBuilding.h"

class BuildingMiner;

class MinerContext : public TickableContext
{
	friend BuildingMiner;

public:
	MinerContext(const Building& building, const Vec2I& pos, Side direction)
		: TickableContext(building, pos, direction, MIDDLE)
	{
	}
};

/**
 * \brief 采掘器
 */
class BuildingMiner final : public TickableBuilding
{
public:
	const static BuildingMiner instance;

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
	bool can_start(TickableContext& context, const GameMap& map) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;
	bool on_finished(TickableContext& context, const GameMap& map) const override;

private:
	explicit BuildingMiner() : TickableBuilding(BuildingSize::small)
	{
	}

	static MinerContext& cast(BuildingContext& context)
	{
		return static_cast<MinerContext&>(context);
	}
};
