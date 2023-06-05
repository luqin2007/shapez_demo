#pragma once
#include "AbstractDrawer.h"
#include "Atlas.h"

class FontDrawer : public AbstractDrawer
{
public:
	explicit FontDrawer(const int count): total_(count)
	{
	}

	/**
	 * \brief 初始化
	 */
	void initialize();

	/**
	 * \brief 准备开始绘制
	 * \param atlas 使用的纹理集
	 */
	void begin(const Atlas& atlas);

	/**
	 * \brief 设置颜色
	 * \param r red 颜色分量
	 * \param g green 颜色分量
	 * \param b blue 颜色分量
	 * \param a alpha 颜色分量
	 */
	void color(float r, float g, float b, float a);

	/**
	 * \brief 绘制文本，默认以高度 48 绘制
	 * \param string 待绘制文本
	 * \param x 中心 x 坐标
	 * \param y0 左上角 y 坐标
	 * \param scale 缩放
	 */
	void push(const char* string, float x, float y0, float scale);

	/**
	 * \brief 绘制
	 */
	void draw();

	/**
	 * \brief 销毁
	 */
	void destroy();

private:
	const int total_;
	int count_;
	const Atlas* at_ = nullptr;
	float* buf_ = nullptr;
};
