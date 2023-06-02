#pragma once

#include "ColoredShapes.h"
#include "TickableBuilding.h"

class Cutter;
class CutterRenderer;

class CutterContext final : public TickableContext
{
	friend Cutter;
	friend CutterRenderer;

public:
	CutterContext(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, MIDDLE)
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
	ColoredShapes left_, right_;
	bool has_shape_ = false;
	bool has_left_ = false, has_right_ = false;

	Vec2I left_pos_, right_pos_;
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

	static CutterContext& cast(BuildingContext& context)
	{
		return static_cast<CutterContext&>(context);
	}

	static const CutterContext& cast(const BuildingContext& context)
	{
		return static_cast<const CutterContext&>(context);
	}

protected:
	bool can_start(const TickableContext& context) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;

private:
	Cutter() = default;
};
