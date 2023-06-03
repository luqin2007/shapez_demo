#include "FontDrawer.h"

void FontDrawer::initialize()
{
	glCreateBuffers(1, &buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, total_ * 24 * sizeof(float), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	create_program(program_, "tex_single.vert", "font.frag", true);
	glUseProgram(program_);
	glUniform4f(1, 0, 0, 0, 1);
	glUniform1i(2, 0);

	glCreateVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void FontDrawer::begin(const Atlas& atlas)
{
	at_ = &atlas;
	glUseProgram(program_);
	glBindVertexArray(vao_);
	glUniform4f(1, 0, 0, 0, 1);
	glUniform1i(2, at_->index_);
}

void FontDrawer::color(const float r, const float g, const float b, const float a)
{
	draw();
	glUniform4f(1, r, g, b, a);
}

void FontDrawer::push(const char* string, float x0, float y0, const float scale)
{
	char ch, name[2];
	int p = 0;
	name[1] = '\0';
	while ((ch = string[p++]))
	{
		if (!at_->chars_.contains(ch))
		{
			char ss[200];
			sprintf_s(ss, 200, "找不到纹理：[%c]", ch);
			throw exception(ss);
		}

		name[0] = ch;
		const auto& [u, v, w, h] = at_->atlas_.at(name);
		const auto& [width, height, bx, by, adv] = at_->chars_.at(ch);

		x0 += bx * scale;
		y0 -= (height - by) * scale;
		const float x1 = width * scale + x0;
		const float y1 = height * scale + y0;

		const float uu = u + w;
		const float vv = v + h;

		if (!buf_)
		{
			buf_ = static_cast<float*>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
		}

		*buf_++ = x0;
		*buf_++ = y0;
		*buf_++ = u;
		*buf_++ = v;

		*buf_++ = x0;
		*buf_++ = y1;
		*buf_++ = u;
		*buf_++ = vv;

		*buf_++ = x1;
		*buf_++ = y0;
		*buf_++ = uu;
		*buf_++ = v;

		*buf_++ = x0;
		*buf_++ = y1;
		*buf_++ = u;
		*buf_++ = vv;

		*buf_++ = x1;
		*buf_++ = y1;
		*buf_++ = uu;
		*buf_++ = vv;

		*buf_++ = x1;
		*buf_++ = y0;
		*buf_++ = uu;
		*buf_++ = v;

		count_++;
		if (count_ == total_)
		{
			draw();
		}

		x0 += (adv >> 6) * scale; // adv * 64
	}
}

void FontDrawer::draw()
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

void FontDrawer::destroy()
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
