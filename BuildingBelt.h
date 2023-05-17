#pragma once

#include <list>

#include "Building.h"
#include "Common.h"

using std::list;
using BI = pair<Item, float>;

class BuildingBelt;

/**
 * \brief 传送带类型
 */
enum class belt_type
{
	/**
	 * \brief 直线
	 */
	direct,

	/**
	 * \brief 向左转向
	 */
	left,

	/**
	 * \brief 向右转向
	 */
	right
};

class BeltContext : public BuildingContext
{
	friend BuildingBelt;

public:
	/**
	 * \brief 传送带类型
	 */
	const belt_type type;

	/**
	 * \brief 传送带中的物品
	 */
	list<BI> items;

	BeltContext(const Building& building, const ivec2& pos, const Side direction, const belt_type type):
		BuildingContext(building, pos, direction), type(type)
	{
		if (type == belt_type::left)
		{
			output_ = --direction;
		}
		else if (type == belt_type::right)
		{
			output_ = ++direction;
		}
		else
		{
			output_ = direction;
		}
	}

private:
	/**
	 * \brief 每 ms 前进速度
	 */
	const float speed_ = 0.2f;

	/**
	 * \brief 传送带最多接收多少物品
	 */
	const int max_item_count_ = 5;

	/**
	 * \brief 输出方向
	 */
	Side output_;
};

/**
 * \brief 传送带
 */
class BuildingBelt : public Building
{
public:
	explicit BuildingBelt(): Building({1, 1})
	{
	}

	bool can_receive(const ivec2& pos, Side side, const BuildingContext& context) const override;
	bool can_receive_item(const Item& item, const ivec2& pos, Side side, const BuildingContext& context) const override;
	void receive(Item item, const ivec2& pos, Side side, BuildingContext& context) const override;
	void update(BuildingContext& context, const GameMap& map) const override;

private:
	static BeltContext& cast(BuildingContext& context)
	{
		return static_cast<BeltContext&>(context);
	}

	static const BeltContext& cast(const BuildingContext& context)
	{
		return static_cast<const BeltContext&>(context);
	}
};
