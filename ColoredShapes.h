#pragma once

#include <utility>

#include "Color.h"
#include "ResourceType.h"
#include "Shape.h"

using std::pair;

/**
 * \brief 由染色后的形状组成的物品
 */
struct ColoredShapes
{
	pair<Color, Shape> down_right;
	pair<Color, Shape> down_left;
	pair<Color, Shape> up_right;
	pair<Color, Shape> up_left;

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
};
