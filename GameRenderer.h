#pragma once

#include <iostream>
#include <map>

#include "BorderDrawer.h"
#include "FontDrawer.h"
#include "Atlas.h"
#include "GameMap.h"
#include "resouces.h"
#include "common.h"
#include "TextureDrawer.h"
#include "ShapeDrawer.h"
#include "vec.h"

using std::map;
using std::cout;
using std::cerr;
using std::endl;

class GameRenderer
{
	friend GameWindow;

public:
	/**
	 * \brief 基于窗口的每条边所在位置 x y 坐标，单位像素
	 */
	Vec2 edge_pos[CELL_COUNT + 1];
	/**
	 * \brief 基于地图的每条边所在原始位置的 x y 坐标，单位像素
	 */
	float edge_pos_base[CELL_COUNT + 1] = {0};

	BorderDrawer map_border_drawer{CELL_COUNT * 2 + 2};
	TextureDrawer tex_drawer{200};
	ShapeDrawer shape_drawer;
	// FontDrawer font_drawer_{ROOT / "font" / "MicrosoftYaHei.ttf"};

	Atlas atlas{4096, 2048, 12, 12};

	void initialize();

	void update(const GameLogic& game);

	void destroy();

	/**
	 * \brief 当网格尺寸大小变化时调用，重新计算基于地图的每个网格的位置
	 * \param map 地图
	 */
	void update_cell_size(const GameMap& map);

	/**
	 * \brief 当网格位置或窗口大小变化时调用，重新计算基于窗口的每个网格的位置
	 * \param map 地图
	 * \param width 窗口宽
	 * \param height 窗口高
	 */
	void update_cell_position(const GameMap& map, float width, float height);

private:
	/// <summary>
	/// cell0_：左上角网格坐标，可被完整显示的第一个点的前一个
	///	cell1_：右下角网格坐标，可被完整显示的最后一个点的后一个
	/// </summary>
	Vec2I cell0_, cell1_;

	void draw_cells();

	void draw_map_resources(const GameMap& map);

	void draw_building(const GameLogic& game, const GameMap& map);

	void draw_ui(const GameLogic& game);

	void draw_overlay(const GameLogic& game, const GameMap& map);
};
