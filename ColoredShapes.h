#pragma once

#include <utility>

#include "Atlas.h"
#include "Color.h"
#include "ResourceType.h"
#include "Shape.h"

using std::pair;

/**
 * \brief 由染色后的形状组成的物品
 */
struct ColoredShapes
{
	pair<Color, Shape> down_right = {Color::uncolored, Shape::none};
	pair<Color, Shape> down_left = { Color::uncolored, Shape::none };
	pair<Color, Shape> up_right = { Color::uncolored, Shape::none };
	pair<Color, Shape> up_left = { Color::uncolored, Shape::none };

	static ColoredShapes from_resource(ResourceType type);

	/**
	 * \brief 顺时针旋转物品
	 */
	void operator++();

	/**
	 * \brief 逆时针旋转物品
	 */
	void operator--();

	/**
	 * \brief 校验该形状是否可以被给定颜色染色
	 * \param color 颜色
	 * \return 是否可被染色
	 */
	bool operator|(Color color) const;

	bool operator==(const ColoredShapes&) const;

	/**
	 * \brief 绘制
	 * \param atlas 纹理集
	 * \param drawer 绘制器
	 * \param x0 x0
	 * \param y0 y0
	 * \param x1 x1
	 * \param y1 y1
	 */
	void draw(const Atlas& atlas, TextureDrawer& drawer, float x0, float y0, float x1, float y1) const;

private:

	static bool get_draw_name(string& name, const pair<Color, Shape>& part);
};
