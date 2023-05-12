#pragma once

#include "Building.h"
#include "Item.h"

class BuildingMiner;

class MinerContext : public BuildingContext
{
	friend BuildingMiner;

public:
	MinerContext(const Building& building, const ivec2& pos, Side direction) : BuildingContext(building, pos, direction)
	{
	}

private:
	long long waiting_time_ = 0;

	long long max_waiting_time_ = 1000;
};

class BuildingMiner : public Building
{
public:
	explicit BuildingMiner() : Building({1, 1})
	{
	}

	bool can_receive(const ivec2& pos, Side side, const BuildingContext& context) const override;
	bool can_receive_item(const Item& item, const ivec2& pos, Side side, const BuildingContext& context) const override;
	void receive(Item item, const ivec2& pos, Side side, BuildingContext& context) const override;
	void update(BuildingContext& context, const GameMap& map) const override;

private:
	static MinerContext& cast(BuildingContext& context)
	{
		return static_cast<MinerContext&>(context);
	}
};
