#pragma once

#include <vector>

#include "Common.h"

using std::vector;

class GameMap;
class Building;
class Item;

/**
 * 表示放置时的状态, NEXT 主要用于地下传送带配对
 */
enum class PlaceState
{
	// 放置完成
	PLACED,
	// 阶段性放置完成
	NEXT,
	// 放置失败
	FAILED
};

/**
 * 建筑在地图上的数据
 */
class BuildingContext
{
public:
	// 建筑类型
	const Building& building;
	// 放置位置
	ivec2 pos;
	// 方向
	Side direction;
	// 放置时间，最后一次更新时间，更新间隔
	long long timePlacer, timeUpdate, timeDelta;
	// 占用的所有位置
	vector<ivec2> all;

	BuildingContext(const Building& building, const ivec2& pos, Side direction, long long timePlacer,
	                long long timeUpdate, long long timeDelta, const vector<ivec2>& all) : building(building),
		pos(pos),
		direction(direction),
		timePlacer(timePlacer),
		timeUpdate(timeUpdate),
		timeDelta(timeDelta),
		all(all)
	{
	}
};

/**
 * 建筑类型，只保存建筑的行为，不保存建筑数据
 */
class Building
{
public:
	/**
	 * 测试是否能正常放下
	 * @param prev 在需要多阶段放置的情况下，记录上次放置的位置；否则为 nullptr
	 */
	virtual bool can_place(const ivec2& pos, Side direction, ivec2* prev, const GameMap& map) const = 0;

	/**
	 * 执行放置操作
	 */
	virtual PlaceState place_at(BuildingContext& context, GameMap& map) const = 0;

	/**
	 * 判断对应位置是否可以接收某物品的输入
	 */
	virtual bool can_receive(Item& item, ivec2& pos, Side side, BuildingContext& context) const = 0;

	/**
	 * 从某位置接收物品
	 */
	virtual void receive(Item& item, ivec2& pos, Side side, BuildingContext& context) const = 0;

	/**
	 * 更新工作状态
	 */
	virtual void update(BuildingContext& context, const GameMap& map) const = 0;
};
