#pragma once

#include "Color.h"
#include "ColoredShapes.h"
#include "TickableBuilding.h"

class Painter;
class PainterRenderer;

class PainterContext final : public TickableContext
{
	friend Painter;
	friend PainterRenderer;

public:
	PainterContext(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, SLOW)
	{
		// 方向向上或向右时向第一个方格输入
		if (direction == Side::up || direction == Side::right)
		{
			left_pos_ = pos;
			right_pos_ = pos + ~direction;
		}
		else
		{
			right_pos_ = pos;
			left_pos_ = pos + ~direction;
		}
	}

private:
	Vec2I left_pos_, right_pos_;
	Color color_ = Color::uncolored;
	ColoredShapes shapes_;
	bool has_shape_ = false;
	bool has_color_ = false;
};

/**
 * \brief 染色器
 */
class Painter final : public TickableBuilding
{
public:
	static const Painter& instance()
	{
		static Painter b;
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

	static const PainterContext& cast(const BuildingContext& context)
	{
		return static_cast<const PainterContext&>(context);
	}

	static PainterContext& cast(BuildingContext& context)
	{
		return static_cast<PainterContext&>(context);
	}

protected:
	bool can_start(const TickableContext& context) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;

private:
	Painter() = default;
};
