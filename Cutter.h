#pragma once

#include "ColoredShapes.h"
#include "TickableBuilding.h"

class Cutter;

class CutterContext final : public TickableContext
{
	friend Cutter;

public:
	CutterContext(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, MIDDLE)
	{
	}

private:
	ColoredShapes shapes_;
	bool has_shape_ = false;
	bool has_left_, has_right_;
};

/**
 * \brief 切割器：将图形物品从中间切成两个
 */
class Cutter final : public TickableBuilding
{
public:
	static const Cutter& instance()
	{
		static Cutter b;
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
	bool can_start(TickableContext& context, const GameMap& map) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;
	bool on_finished(TickableContext& context, const GameMap& map) const override;

private:
	Cutter() = default;

	static void send_shape_items(CutterContext& context, const GameMap& map);

	static CutterContext& cast(BuildingContext& context)
	{
		return static_cast<CutterContext&>(context);
	}

	static const CutterContext& cast(const BuildingContext& context)
	{
		return static_cast<const CutterContext&>(context);
	}
};
