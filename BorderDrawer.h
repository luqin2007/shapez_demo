#pragma once

#include "AbstractDrawer.h"

/**
 * \brief 用于边界的直线渲染，颜色为 0xF6F6F6
 */
class BorderDrawer: public AbstractDrawer
{
public:
	/**
	 * \param count 批量绘制个数
	 */
	explicit BorderDrawer(const int count) : total_(count)
	{
	}

	/**
	 * \brief 初始化
	 */
	void initialize();

	/**
	 * \brief 准备绘制
	 */
	void begin() const;

	/**
	 * \brief 传入一条直线的两个顶线
	 * \param x0 第一个顶点的 x 坐标，单位像素
	 * \param y0 第一个顶点的 y 坐标，单位像素
	 * \param x1 第二个顶点的 x 坐标，单位像素
	 * \param y1 第二个顶点的 y 坐标，单位像素
	 */
	void push(float x0, float y0, float x1, float y1);

	/**
	 * \brief 绘制已缓存顶点
	 */
	void draw();

	/**
	 * \brief 销毁
	 */
	void destroy();

private:
	/**
	 * \brief 批量绘制最大量
	 */
	const int total_;

	/**
	 * \brief 未被绘制直线量
	 */
	int count_ = 0;

	/**
	 * \brief 顶点缓冲区指针
	 */
	float* buf_ = nullptr;
};
