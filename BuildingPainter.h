#pragma once

#include "Color.h"
#include "ColoredShapes.h"
#include "TickableBuilding.h"

class BuildingPainter;

class PainterContext : public TickableContext
{
	friend BuildingPainter;

public:
	PainterContext(const Building& building, const Vec2I& pos, Side direction)
		: TickableContext(building, pos, direction, SLOW)
	{
	}

private:
	Color color_ = Color::uncolored;
	ColoredShapes shapes_;
	bool has_shape_ = false;
	bool has_color_ = false;
};

/**
 * \brief 染色器
 */
class BuildingPainter final : public TickableBuilding
{
public:
	static const BuildingPainter& instance()
	{
		static BuildingPainter b;
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

protected:
	bool can_start(TickableContext& context, const GameMap& map) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;
	bool on_finished(TickableContext& context, const GameMap& map) const override;

private:
	BuildingPainter() : TickableBuilding(BuildingSize::middle, "painter.png", "painter.png", "painter_blue.png")
	{
	}

	static const PainterContext& cast(const BuildingContext& context)
	{
		return static_cast<const PainterContext&>(context);
	}

	static PainterContext& cast(BuildingContext& context)
	{
		return static_cast<PainterContext&>(context);
	}
};
