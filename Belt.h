#pragma once

#include "Building.h"
#include "Belt.h"
#include "BuildingContext.h"
#include "ColoredShapes.h"
#include "GameLogic.h"
#include "ItemType.h"

using std::list;
using std::pair;

class Belt;
class Belts;
class BeltDirectRenderer;
class BeltLeftRenderer;
class BeltRightRenderer;

class BeltContext final : public BuildingContext
{
	friend Belt;
	friend BeltDirectRenderer;
	friend BeltLeftRenderer;
	friend BeltRightRenderer;
	
	/**
	 * \brief 传送带上的物品
	 */
	ItemType item_types_[2] = {ItemType::none, ItemType::none};
	Color dyes_[2] = {Color::uncolored, Color::uncolored};
	ColoredShapes shapes_[2];
	int first_ = 0, second_ = 1;

	/**
	 * \brief 每秒前进速度
	 */
	const float speed_ = 0.25f;
	time_t place_time_;

	/**
	 * \brief 当前传送带上物品个数
	 */
	int item_count_ = 0;

	/**
	 * \brief 输出位置
	 */
	const Side output_;

	/**
	 * \brief 传送带上物品的位置
	 */
	float item_pos_[2] = {0, 0};

public:
	BeltContext(const Building& building, const Vec2I& pos, const Side direction, const Side output):
		BuildingContext(building, pos, direction), place_time_(current_game->timer().running_ms), output_(output)
	{
	}

};

/**
 * \brief 传送带
 */
class Belt : public Building
{
	friend Belts;

public:
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
	[[nodiscard]] vector<Vec2I> all_positions(const Vec2I& pos, Side direction) const override;

	static BeltContext& cast(BuildingContext& context)
	{
		return static_cast<BeltContext&>(context);
	}

	static const BeltContext& cast(const BuildingContext& context)
	{
		return static_cast<const BeltContext&>(context);
	}

protected:
	Belt() = default;
};

/**
 * \brief 传送带：直行
 */
class BeltDirect final : public Belt
{
	friend Belts;

public:
	[[nodiscard]] BuildingContext* build_context(const Vec2I& pos, Side direction) const override;
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;

private:
	BeltDirect() = default;
};

/**
 * \brief 传送带：向左转弯
 */
class BeltLeft final : public Belt
{
	friend Belts;

public:
	[[nodiscard]] BuildingContext* build_context(const Vec2I& pos, Side direction) const override;
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;

private:
	BeltLeft() = default;
};

/**
 * \brief 传送带：向右转弯
 */
class BeltRight final : public Belt
{
	friend Belts;

public:
	[[nodiscard]] BuildingContext* build_context(const Vec2I& pos, Side direction) const override;
	[[nodiscard]] const BuildingRenderer& get_renderer() const override;

private:
	BeltRight() = default;
};

/**
 * \brief 获取传送带建筑实例
 */
class Belts
{
public:
	static const Belt& direct();
	static const Belt& left();
	static const Belt& right();
};
