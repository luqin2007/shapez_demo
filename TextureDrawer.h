#pragma once

#include "AbstractDrawer.h"
#include "Atlas.h"
#include "Side.h"

/**
 * \brief 批量在地图上绘制纹理，每个矩形需要 24 个 float
 *
 * 给定纹理达到最大数量后会直接绘制，否则当 draw 调用时绘制
 */
class TextureDrawer : public AbstractDrawer
{
public:
	explicit TextureDrawer(const int count): total_(count)
	{
	}

	/**
	 * \brief 初始化
	 */
	void initialize();

	/**
	 * \brief 准备开始绘制
	 */
	void begin();

	/**
	 * \brief 半透明纹理
	 * \param alpha 纹理整体 alpha 值
	 */
	void alpha(GLfloat alpha);

	/**
	 * \brief 插入纹理
	 * \param x0 左上角顶点的 x 坐标，单位像素
	 * \param y0 左上角顶点的 y 坐标，单位像素
	 * \param x1 右下角顶点的 x 坐标，单位像素
	 * \param y1 右下角顶点的 y 坐标，单位像素
	 * \param atlas 所在纹理集
	 * \param name 纹理名称
	 * \param side 纹理方向
	 * \param opaque 是否以不透明的形式渲染
	 */
	void push(float x0, float y0, float x1, float y1, const Atlas& atlas, const string& name, Side side = Side::up,
	          bool opaque = false);

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
	int count_ = 0;
	GLint tex_ = 0;
	GLfloat alpha_ = 1;
	// 不透明状态
	GLfloat op_alpha_ = -1;
	float* buf_ = nullptr;

	inline void push_vertices(float x0, float y0, float x1, float y1,
	                          float u0, float v0, float u1, float v1,
	                          float u2, float v2, float u3, float v3);
};
