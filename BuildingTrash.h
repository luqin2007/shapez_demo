#pragma once
#include "Building.h"
#include "BuildingContext.h"

class TrashContext : public BuildingContext
{
public:
	TrashContext(const Building& building, const Vec2I& pos, Side direction)
		: BuildingContext(building, pos, direction)
	{
	}
};

/**
 * \brief 垃圾桶，移除所有物品
 */
class BuildingTrash : public Building
{
public:
	static const BuildingTrash instance;

	[[nodiscard]] BuildingContext build_context(const Vec2I& pos, Side direction) const override;
	[[nodiscard]] bool can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const override;
	[[nodiscard]] bool
	can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const override;
	[[nodiscard]] bool can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                                     const BuildingContext& context) const override;
	void receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const override;
	void receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                   BuildingContext& context) const override;
	void update(BuildingContext& context, GameMap& map) const override;

private:
	explicit BuildingTrash() : Building(BuildingSize::small)
	{
	}
};
