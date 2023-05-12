#pragma once

#include <list>

#include "Building.h"
#include "Common.h"

using std::list;
using BI = pair<Item, float>;

class BuildingBelt;

enum class BeltType
{
	DIRECT,
	LEFT,
	RIGHT
};

class BeltContext : public BuildingContext
{
	friend BuildingBelt;

public:
	const BeltType type;

	list<BI> items;

	BeltContext(const Building& building, const ivec2& pos, const Side direction, const BeltType type):
		BuildingContext(building, pos, direction), type(type)
	{
		if (type == BeltType::LEFT)
		{
			output_ = --direction;
		}
		else if (type == BeltType::RIGHT)
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
