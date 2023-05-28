#pragma once

#include "vec.h"

class Building;
enum class Side;

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
	Vec2I pos;

	/**
	 * \brief 主要输出方向（通常为 up）
	 */
	Side direction;
	
	BuildingContext(const Building& building, const Vec2I& pos, const Side direction) :
		building(building), pos(pos), direction(direction)
	{
	}
};