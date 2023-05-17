#pragma once

#include "AbstractDrawer.h"
#include "Common.h"

/**
 * \brief 批量绘制纹理，每个矩形需要 24 个 float
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
	void begin() const;

	/**
	 * \brief 设置纹理索引
	 * \param tex 纹理索引
	 */
	void tex(GLint tex);

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
	 * \param u 左上角顶点 x 纹理坐标
	 * \param v 左上角顶点 y 纹理坐标
	 * \param w 纹理宽度，[0, 1]
	 * \param h 纹理高度，[0, 1]
	 */
	void push(float x0, float y0, float x1, float y1, float u, float v, float w, float h);

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
	GLfloat alpha_ = 0;
	float* buf_ = nullptr;
};
