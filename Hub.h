#pragma once

#include "Building.h"
#include "BuildingContext.h"
#include "ColoredShapes.h"

using std::make_unique;

class HubContext : public BuildingContext
{
public:
	/**
	 * \brief 当前等级需要的物品个数
	 */
	int total_count = 0;

	/**
	 * \brief 当前等级需要的物品类型
	 */
	ColoredShapes shapes;

	/**
	 * \brief 当前等级已提交物品个数
	 */
	int accept_count = 0;

	/**
	 * \brief 当前等级
	 */
	int level = 0;

	HubContext(const Building& building, const Vec2I& pos, const Side direction)
		: BuildingContext(building, pos, direction)
	{
	}
};

/**
 * \brief 中心 任务提交器
 */
class Hub final : public Building
{
public:
	static const Hub& instance()
	{
		static Hub b;
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
	void update(BuildingContext& context, GameMap& map) const override;
	void free_context(BuildingContext* context) const override;
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;
	[[nodiscard]] vector<Vec2I> all_positions(const Vec2I& pos, Side direction) const override;

private:
	Hub() = default;

	static HubContext& cast(BuildingContext& context)
	{
		return static_cast<HubContext&>(context);
	}

	static void set_next_level(HubContext& context);

	static Color random_color(int level);

	static Shape random_shape();
};
