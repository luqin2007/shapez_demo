#pragma once

#include <string>

#include "Color.h"
#include "Side.h"
#include "vec.h"

using std::string;

struct ColoredShapes;
class GameMap;
class BuildingContext;
class GameRenderer;

constexpr static float ICON_PADDING = 5;
constexpr static float EXT_SIZE = 1;

/**
 * \brief 建筑渲染器
 */
class BuildingRenderer
{
public:
	virtual ~BuildingRenderer() = default;
	/**
	 * \brief 渲染地图上的建筑
	 * \param row 行
	 * \param col 列
	 * \param context 建筑信息
	 * \param renderer 游戏主渲染器
	 * \param map 地图
	 */
	virtual void draw_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                           const GameMap& map) const = 0;

	/**
	 * \brief 渲染持有的建筑
	 * \param x 基于窗口的 x 坐标
	 * \param y 基于窗口的 y 坐标
	 * \param direction 方向
	 * \param renderer 游戏主渲染器
	 * \param map 地图
	 */
	virtual void draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const = 0;

	/**
	 * \brief 渲染建筑图标
	 * \param x 基于窗口的 x 坐标
	 * \param y 基于窗口的 y 坐标
	 * \param size 按钮大小
	 * \param renderer 游戏主渲染器
	 */
	virtual void draw_icon(float x, float y, float size, GameRenderer& renderer) const = 0;

	/**
	 * \brief 渲染建筑叠加层，在游戏其他部分都渲染完成后渲染
	 * \param row 行
	 * \param col 列
	 * \param context 建筑信息
	 * \param renderer 游戏主渲染器
	 * \param map 地图
	 */
	virtual void draw_overlay(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                          const GameMap& map) const = 0;

protected:
	/**
	 * \brief 绘制染料对应的物品
	 * \param x0 左上角 x
	 * \param y0 左上角 y
	 * \param cell_size 网格大小
	 * \param renderer 游戏主渲染器
	 * \param color 染料颜色
	 */
	static void draw_color(float x0, float y0, float cell_size, GameRenderer& renderer, Color color);

	/**
	 * \brief 渲染形状物品
	 * \param x0 左上角 x
	 * \param y0 左上角 y
	 * \param cell_size 网格大小
	 * \param renderer 游戏主渲染器
	 * \param item 物品
	 */
	static void draw_item(float x0, float y0, float cell_size, GameRenderer& renderer, const ColoredShapes& item);
};
