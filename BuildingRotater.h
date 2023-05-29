#pragma once

#include "TickableBuilding.h"
#include "ColoredShapes.h"

class BuildingRotater;

class RotaterContext : public TickableContext
{
	friend BuildingRotater;

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
class BuildingRotater : public TickableBuilding
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

protected:
	bool can_start(TickableContext& context, const GameMap& map) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;
	bool on_finished(TickableContext& context, const GameMap& map) const override;

	virtual void rotate_item(ColoredShapes& shape) const = 0;

	BuildingRotater() : TickableBuilding(BuildingSize::small, "rotater.png", "rotater.png", "rotater_blue.png")
	{
	}

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
 * \brief 向左旋转
 */
class BuildingRotaterL final : public BuildingRotater
{
public:
	static const BuildingRotaterL& instance()
	{
		static BuildingRotaterL b;
		return b;
	}

protected:
	void rotate_item(ColoredShapes& item) const override
	{
		--item;
	}
};

/**
 * \brief 向右旋转
 */
class BuildingRotaterR final : public BuildingRotater
{
public:
	static const BuildingRotaterR& instance()
	{
		static BuildingRotaterR b;
		return b;
	}

protected:
	BuildingRotaterR()
	{
		next_variant = &BuildingRotaterL::instance();
		const_cast<BuildingRotaterL&>(BuildingRotaterL::instance()).next_variant = this;
	}

	void rotate_item(ColoredShapes& item) const override
	{
		++item;
	}
};
