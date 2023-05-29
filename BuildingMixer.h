#pragma once

#include "TickableBuilding.h"
#include "Color.h"

class BuildingMixer;

class MixerContext : public TickableContext
{
	friend BuildingMixer;

public:
	MixerContext(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, SLOW)
	{
	}

private:
	Color color1_ = Color::uncolored, color2_ = Color::uncolored;
};

/**
 * \brief 颜色混合器
 */
class BuildingMixer final : public TickableBuilding
{
public:
	static const BuildingMixer& instance()
	{
		static BuildingMixer b;
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
	BuildingMixer() : TickableBuilding(BuildingSize::middle, "mixer.png", "mixer.png", "mixer_blue.png")
	{
	}

	static MixerContext& cast(BuildingContext& context)
	{
		return static_cast<MixerContext&>(context);
	}

	static const MixerContext& cast(const BuildingContext& context)
	{
		return static_cast<const MixerContext&>(context);
	}
};
