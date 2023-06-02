#pragma once

#include "TickableBuilding.h"
#include "ColoredShapes.h"

class Rotater;
class Rotaters;
class RotaterRenderer;

class RotaterContext final : public TickableContext
{
	friend Rotater;
	friend RotaterRenderer;

public:
	RotaterContext(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, FAST)
	{
	}

private:
	ColoredShapes shapes_;
	bool has_shape_ = false;
};

/**
 * \brief 旋转物品
 */
class Rotater : public TickableBuilding
{
public:
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
	[[nodiscard]] vector<Vec2I> all_positions(const Vec2I& pos, Side direction) const override;

protected:
	bool can_start(const TickableContext& context) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;

	virtual void rotate_item(ColoredShapes& shape) const = 0;

	Rotater() = default;

	static RotaterContext& cast(BuildingContext& context)
	{
		return static_cast<RotaterContext&>(context);
	}

	static const RotaterContext& cast(const BuildingContext& context)
	{
		return static_cast<const RotaterContext&>(context);
	}
};

/**
 * \brief 顺时针旋转
 */
class RotaterCW final : public Rotater
{
	friend Rotaters;

public:
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;

protected:
	RotaterCW() = default;

	void rotate_item(ColoredShapes& item) const override
	{
		--item;
	}
};

/**
 * \brief 逆时针旋转
 */
class RotaterCCW final : public Rotater
{
	friend Rotaters;

public:
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;

protected:
	RotaterCCW() = default;

	void rotate_item(ColoredShapes& item) const override
	{
		++item;
	}
};

class Rotaters
{
public:
	static const Rotater& cw();
	static const Rotater& ccw();
};
