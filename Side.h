#pragma once

/**
 * \brief 方向
 */
enum class Side
{
	up,
	down,
	left,
	right
};

/**
 * 顺时针旋转
 */
Side cw(Side side);

/**
 * 逆时针旋转
 */
Side ccw(Side side);

/**
 * 反向
 */
Side opposite(Side side);

/**
 * 取建筑蔓延方向
 */
Side operator~(Side side);