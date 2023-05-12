#pragma once

#include <vector>

#include "Common.h"
#include "GameMap.h"

using std::vector;

class Item;
class Building;

/**
 * \brief 建筑在地图上的数据
 */
class BuildingContext
{
public:
	/**
	 * \brief 建筑类型
	 */
	const Building& building;

	/**
	 * \brief 放置位置
	 */
	ivec2 pos;

	/**
	 * \brief 方向，默认为 DOWN
	 */
	Side direction;

	BuildingContext(const Building& building, const ivec2& pos, const Side direction) :
		building(building), pos(pos), direction(direction)
	{
	}
};

/**
 * \brief 建筑类型，只保存建筑的行为，不保存建筑数据
 */
class Building
{
public:
	/**
	 * \brief 建筑大小 
	 */
	const ivec2 size;

	virtual ~Building() = default;

	explicit Building(const ivec2& size): size(size)
	{
	}

	/**
	 * \brief 测试是否能正常放下
	 * \param pos 建筑所在位置
	 * \param direction 建筑方向
	 * \param map 地图
	 */
	bool can_place(const ivec2& pos, Side direction, const GameMap& map) const;

	/**
	 * \brief 判断对应位置是否可能接收物品输入
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	virtual bool can_receive(const ivec2& pos, Side side, const BuildingContext& context) const = 0;

	/**
	 * \brief 判断对应位置是否可以输入某物品
	 * \param item 输入的物品
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	virtual bool can_receive_item(const Item& item, const ivec2& pos, Side side,
	                              const BuildingContext& context) const = 0;

	/**
	 * \brief 从某位置接收物品，调用该方法之前应当保证通过 can_receive_item 检验
	 * \param item 输入物品
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	virtual void receive(Item item, const ivec2& pos, Side side, BuildingContext& context) const = 0;

	/**
	 *\brief 更新建筑状态
	 */
	virtual void update(BuildingContext& context, const GameMap& map) const = 0;

	/**
	 * \brief 获取建筑占用的所有方块
	 * \param pos 建筑所在位置
	 * \param direction 建筑方向
	 * \return 所有方向
	 */
	static vector<ivec2> all_positions(const ivec2& pos, Side direction);

	/**
	 * \brief 尝试向某个方向发送物品
	 * \param pos 发出点
	 * \param direction 发送方向 
	 * \param item 发送物品
	 * \param map 地图
	 * \return 是否成功发送
	 */
	static bool send_item(const ivec2& pos, const Side direction, const Item& item, const GameMap& map)
	{
		const ivec2 target = pos + direction;
		if (BuildingContext* t_context = map.get_building(target);
			t_context && t_context->building.can_receive_item(item, target, -direction, *t_context))
		{
			t_context->building.receive(item, target, -direction, *t_context);
			return true;
		}

		return false;
	}
};
