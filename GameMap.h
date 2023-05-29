#pragma once

#include <string>
#include <memory>
#include <functional>

#include "Common.h"
#include "ResourceType.h"
#include "vec.h"

class Building;
class BuildingContext;

using std::string;
using std::function;
using std::unique_ptr;

/**
 * \brief 游戏地图
 */
class GameMap
{
public:
	/**
	 * \brief 屏幕中点对应第 center.x 行，第 center.y 列
	 */
	Vec2 center{CELL_COUNT / 2.0f, CELL_COUNT / 2.0f};

	/**
	 * \brief 每一个单元格的长度
	 */
	float cell_size = 100;

	GameMap();

	/**
	 * \brief 初始化
	 */
	void initialize();

	[[nodiscard]]
	ResourceType get_resource(int x, int y) const;

	[[nodiscard]]
	ResourceType get_resource(const Vec2I& pos) const
	{
		return get_resource(pos.x, pos.y);
	}

	bool set_building(int x, int y, const Building* building, Side direction);

	[[nodiscard]]
	BuildingContext* get_building(int x, int y) const;

	[[nodiscard]]
	BuildingContext* get_building(const Vec2I& pos) const
	{
		return get_building(pos.x, pos.y);
	}

	void remove_building(int x, int y);

private:
	/**
	 * \brief 地图资源
	 */
	ResourceType resources_[CELL_COUNT][CELL_COUNT]{};

	/**
	 * \brief 地图建筑
	 */
	BuildingContext* buildings_[CELL_COUNT][CELL_COUNT]{};
};
