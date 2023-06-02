#pragma once

#include "TickableBuilding.h"

/**
 * \brief 采掘器
 */
class Miner final : public TickableBuilding
{
public:
	static const Miner& instance()
	{
		static Miner b;
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
	bool can_start(const TickableContext& context) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;

	Miner() = default;
};
