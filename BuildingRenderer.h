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
class TickableContext;

constexpr static float ICON_PADDING = 5;
constexpr static float EXT_SIZE = 1;

/**
 * \brief 建筑渲染器
 */
class BuildingRenderer
{
public:
	/**
	 * \brief 建筑本体是否在物品之下
	 */
	const bool under_item;

	virtual ~BuildingRenderer() = default;

	explicit BuildingRenderer(const bool under_item = false): under_item(under_item)
	{
	}

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
	 * \brief 渲染建筑中的物品
	 * \param row 建筑所在行
	 * \param col 建筑所在列
	 * \param context 建筑信息
	 * \param renderer 游戏主渲染器
	 * \param map 地图
	 */
	virtual void draw_items_in_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                                    const GameMap& map) const = 0;

	/**
	 * \brief 渲染建筑图标
	 * \param x 基于窗口的 x 坐标
	 * \param y 基于窗口的 y 坐标
	 * \param size 按钮大小
	 * \param renderer 游戏主渲染器
	 */
	virtual void draw_icon(float x, float y, float size, GameRenderer& renderer) const = 0;

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

	/**
	 * \brief 绘制指定纹理到输出口
	 * \param row 行
	 * \param col 列
	 * \param cell_size 网格大小
	 * \param direction 输出方向
	 * \param renderer 游戏主渲染器
	 * \param texture 纹理名
	 * \param ctx 建筑数据
	 */
	static void draw_output_texture(int row, int col, float cell_size, Side direction,
	                                GameRenderer& renderer, const string& texture, const TickableContext& ctx);

	/**
	 * \brief 绘制染料对应的物品到输出口
	 * \param row 行
	 * \param col 列
	 * \param cell_size 网格大小
	 * \param direction 输出方向
	 * \param renderer 游戏主渲染器
	 * \param color 染料颜色
	 * \param ctx 建筑数据
	 */
	static void draw_output_color(int row, int col, float cell_size, Side direction,
	                              GameRenderer& renderer, Color color, const TickableContext& ctx);

	/**
	 * \brief 渲染形状物品到输出口
	 * \param row 行
	 * \param col 列
	 * \param cell_size 网格大小
	 * \param direction 输出方向
	 * \param renderer 游戏主渲染器
	 * \param item 物品
	 * \param ctx 建筑数据
	 */
	static void draw_output_item(int row, int col, float cell_size, Side direction,
	                             GameRenderer& renderer, const ColoredShapes& item, const TickableContext& ctx);

private:
	static Vec2 offset_item(Side direction, float cell_size, float p, float x0, float y0);
};
