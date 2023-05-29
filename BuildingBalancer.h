#pragma once

#include <queue>

#include "TickableBuilding.h"

using std::queue;

class BuildingBalancer;

class BalancerContext final : public TickableContext
{
	friend BuildingBalancer;

public:
	BalancerContext(const Building& building, const Vec2I& pos, const Side direction)
		: TickableContext(building, pos, direction, FAST)
	{
	}

private:
	/**
	 * \brief 平衡器中持有的图形
	 */
	queue<ColoredShapes> shapes_;

	/**
	 * \brief 平衡器中持有的颜色
	 */
	queue<Color> colors_;

	/**
	 * \brief 平衡器中物品的类型序列
	 */
	queue<ItemType> types_;

	/**
	 * \brief 下一次优先输出方向
	 */
	int side_ = 0;

	/**
	 * \brief 可接受的物品个数
	 */
	queue<unique_ptr<ItemType>>::size_type max_items_ = 3;
};

/**
 * \brief 平衡器：两个输入，两个输出交替输出
 */
class BuildingBalancer final : public TickableBuilding
{
public:
	static const BuildingBalancer& instance()
	{
		static BuildingBalancer s;
		return s;
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

	BuildingBalancer() : TickableBuilding(BuildingSize::middle, "balancer.png", "balancer.png", "balancer_blue.png")
	{
	}

	[[nodiscard]]
	bool can_receive(Side side, const BuildingContext& context) const;

	static void send_first_item(BalancerContext& context, const GameMap& map);

	static BalancerContext& cast(BuildingContext& context)
	{
		return static_cast<BalancerContext&>(context);
	}

	static const BalancerContext& cast(const BuildingContext& context)
	{
		return static_cast<const BalancerContext&>(context);
	}
};
