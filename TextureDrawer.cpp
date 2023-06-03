#include "TextureDrawer.h"

#include "./math.h"

void TextureDrawer::initialize()
{
	glCreateBuffers(1, &buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, total_ * 24 * sizeof(float), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	create_program(program_, "tex_single.vert", "tex_alpha.frag", true);
	glUseProgram(program_);
	glUniform1i(1, 0);
	glUniform1f(2, 1.0f);

	glCreateVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void TextureDrawer::begin()
{
	glUseProgram(program_);
	glBindVertexArray(vao_);

	alpha(1);
	op_alpha_ = -1;
}

void TextureDrawer::alpha(const GLfloat alpha)
{
	if (!feq(alpha, alpha_))
	{
		draw();
		alpha_ = alpha;
		glUniform1f(2, alpha);
	}
}

void TextureDrawer::push(const float x0, const float y0, float x1, float y1,
                         const Atlas& atlas, const string& name, const Side side, const bool opaque)
{
	if (!atlas.atlas_.contains(name))
	{
		char ss[200];
		sprintf_s(ss, 200, "找不到纹理：[%s]", name.c_str());
		throw exception(ss);
	}

	// 切换纹理集
	if (tex_ != atlas.index_)
	{
		draw();
		tex_ = atlas.index_;
		glUniform1i(1, atlas.index_);
	}

	// 检查透明度
	if (opaque)
	{
		if (!feq(1.0f, alpha_))
		{
			op_alpha_ = alpha_;
			alpha(1);
		}
	}
	else
	{
		if (op_alpha_ >= 0 && !feq(alpha_, op_alpha_))
		{
			alpha(op_alpha_);
			op_alpha_ = -1;
		}
	}

	const auto& [u, v, w, h] = atlas.atlas_.at(name);

	const float uu = u + w;
	const float vv = v + h;

	const float dx = x1 - x0;
	const float dy = y1 - y0;

	float u0, v0, u1, v1, u2, v2, u3, v3;
	switch (side)
	{
	case Side::up:
		u0 = u;
		v0 = vv;
		u1 = u;
		v1 = v;
		u2 = uu;
		v2 = v;
		u3 = uu;
		v3 = vv;
		break;

	case Side::down:
		u0 = uu;
		v0 = v;
		u1 = uu;
		v1 = vv;
		u2 = u;
		v2 = vv;
		u3 = u;
		v3 = v;
		break;

	case Side::left:
		// 逆时针 90°
		x1 = x0 + dy;
		y1 = y0 + dx;
		u0 = uu;
		v0 = vv;
		u1 = u;
		v1 = vv;
		u2 = u;
		v2 = v;
		u3 = uu;
		v3 = v;
		break;

	case Side::right:
		// 顺时针 90°
		x1 = x0 + dy;
		y1 = y0 + dx;
		u0 = u;
		v0 = v;
		u1 = uu;
		v1 = v;
		u2 = uu;
		v2 = vv;
		u3 = u;
		v3 = vv;
		break;
	}
	if (atlas.dot9s_.contains(name))
	{
		// 绘制 .9 图
		const auto& [up, down, left, right] = atlas.dot9s_.at(name);
		// 旋转后中间部分的 uv
		float nu0, nv0, nu1, nv1, nu2, nv2, nu3, nv3;
		// 旋转后四周的距离
		float pu, pd, pl, pr;

		switch (side)
		{
		case Side::up:
			pu = up;
			pr = right;
			pd = down;
			pl = left;

			nu0 = u + left / atlas.width_;
			nv0 = vv - up / atlas.height_;
			nu1 = u + left / atlas.width_;
			nv1 = v + down / atlas.height_;
			nu2 = uu - right / atlas.width_;
			nv2 = v + down / atlas.height_;
			nu3 = uu - right / atlas.width_;
			nv3 = vv - up / atlas.height_;
			break;
		case Side::down:
			pu = down;
			pr = left;
			pd = up;
			pl = right;

			nu0 = u + left / atlas.width_;
			nv0 = v + down / atlas.height_;
			nu1 = u + left / atlas.width_;
			nv1 = vv - up / atlas.height_;
			nu2 = uu - right / atlas.width_;
			nv2 = vv - up / atlas.height_;
			nu3 = uu - right / atlas.width_;
			nv3 = v + down / atlas.height_;
			break;
		case Side::left:
			pu = right;
			pr = down;
			pd = left;
			pl = up;

			nu0 = uu - right / atlas.width_;
			nv0 = vv - up / atlas.height_;
			nu1 = u + left / atlas.width_;
			nv1 = vv - up / atlas.height_;
			nu2 = u + left / atlas.width_;
			nv2 = v + down / atlas.height_;
			nu3 = uu - right / atlas.width_;
			nv3 = v + down / atlas.height_;
			break;
		case Side::right:
			pu = left;
			pr = up;
			pd = right;
			pl = down;

			nu0 = u + left / atlas.width_;
			nv0 = v + down / atlas.height_;
			nu1 = uu - right / atlas.width_;
			nv1 = v + down / atlas.height_;
			nu2 = uu - right / atlas.width_;
			nv2 = vv - up / atlas.height_;
			nu3 = u + left / atlas.width_;
			nv3 = vv - up / atlas.height_;
			break;
		}

		// 左上角
		push_vertices(x0, y0, x0 + pl, y0 + pu, u0, v0, u0, nv0, nu0, nv0, nu0, v0);
		// 左下角
		push_vertices(x0, y1 - pd, x0 + pl, y1, u1, nv1, u1, v1, nu1, v1, nu1, nv1);
		// 右下角
		push_vertices(x1 - pr, y1 - pd, x1, y1, nu2, nv2, nu2, v2, u2, v2, u2, nv2);
		// 右上角
		push_vertices(x1 - pr, y0, x1, y0 + pu, nu3, v3, nu3, nv3, u3, nv3, u3, v3);
		// 左侧
		push_vertices(x0, y0 + pu, x0 + pl, y1 - pd, u0, nv0, u1, nv1, nu1, nv1, nu0, nv0);
		// 底部
		push_vertices(x0 + pl, y1 - pd, x1 - pr, y1, nu1, nv1, nu1, v1, nu2, v2, nu2, nv2);
		// 右侧
		push_vertices(x1 - pr, y0 + pu, x1, y1 - pd, nu3, nv3, nu2, nv2, u2, nv2, u3, nv3);
		// 顶部
		push_vertices(x0 + pl, y0, x1 - pr, y0 + pu, nu0, v0, nu0, nv0, nu3, nv3, nu3, v3);
		// 中间
		push_vertices(x0 + pl, y0 + pu, x1 - pr, y1 - pd, nu0, nv0, nu1, nv1, nu2, nv2, nu3, nv3);
	}
	else
	{
		// 绘制普通纹理
		push_vertices(x0, y0, x1, y1, u0, v0, u1, v1, u2, v2, u3, v3);
	}
}

void TextureDrawer::draw()
{
	if (buf_)
	{
		glUnmapNamedBuffer(buffer_);
		buf_ = nullptr;
	}

	if (count_)
	{
		glDrawArrays(GL_TRIANGLES, 0, count_ * 6);
		count_ = 0;
	}
}

void TextureDrawer::destroy()
{
	if (buf_)
	{
		glUnmapNamedBuffer(buffer_);
		buf_ = nullptr;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);

	glDeleteProgram(program_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &buffer_);
}

void TextureDrawer::push_vertices(const float x0, const float y0, const float x1, const float y1,
                                  const float u0, const float v0, const float u1, const float v1,
                                  const float u2, const float v2, const float u3, const float v3)
{
	if (!buf_)
	{
		buf_ = static_cast<float*>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
	}

	*buf_++ = x0;
	*buf_++ = y0;
	*buf_++ = u0;
	*buf_++ = v0;

	*buf_++ = x0;
	*buf_++ = y1;
	*buf_++ = u1;
	*buf_++ = v1;

	*buf_++ = x1;
	*buf_++ = y0;
	*buf_++ = u3;
	*buf_++ = v3;

	*buf_++ = x0;
	*buf_++ = y1;
	*buf_++ = u1;
	*buf_++ = v1;

	*buf_++ = x1;
	*buf_++ = y1;
	*buf_++ = u2;
	*buf_++ = v2;

	*buf_++ = x1;
	*buf_++ = y0;
	*buf_++ = u3;
	*buf_++ = v3;

	count_++;
	if (count_ == total_)
	{
		draw();
	}
}
