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
Side operator++(Side side);

/**
 * 逆时针旋转
 */
Side operator--(Side side);

/**
 * 反向
 */
Side operator-(Side side);