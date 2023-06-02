#pragma once

#include "TickableBuilding.h"
#include "Color.h"

class Mixer;
class MixerRenderer;

class MixerContext final : public TickableContext
{
	friend Mixer;
	friend MixerRenderer;

public:
	MixerContext(const Building& building, const Vec2I& pos, const Side direction)
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
	Color color_left_ = Color::uncolored, color_right_ = Color::uncolored;
};

/**
 * \brief 颜色混合器
 */
class Mixer final : public TickableBuilding
{
public:
	static const Mixer& instance()
	{
		static Mixer b;
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

	static MixerContext& cast(BuildingContext& context)
	{
		return static_cast<MixerContext&>(context);
	}

	static const MixerContext& cast(const BuildingContext& context)
	{
		return static_cast<const MixerContext&>(context);
	}

protected:
	bool can_start(const TickableContext& context) const override;
	bool on_blocking(TickableContext& context, const GameMap& map) const override;

private:
	Mixer() = default;
};
