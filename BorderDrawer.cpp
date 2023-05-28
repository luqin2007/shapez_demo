#include "BorderDrawer.h"

#include <glad/glad.h>

void BorderDrawer::initialize()
{
	create_program(program_, "cell_border.vert", "cell_border.frag", true);
	// 顶点缓冲区
	glCreateBuffers(1, &buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, total_ * 4 * sizeof(float), nullptr, GL_MAP_WRITE_BIT | GL_MAP_READ_BIT);
	// 顶点数组对象
	glCreateVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void BorderDrawer::begin() const
{
	glUseProgram(program_);
	glBindVertexArray(vao_);
}

void BorderDrawer::push(const float x0, const float y0, const float x1, const float y1)
{
	if (!buf_)
	{
		buf_ = static_cast<float*>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
		count_ = 0;
	}

	*buf_++ = x0;
	*buf_++ = y0;
	*buf_++ = x1;
	*buf_++ = y1;
	count_++;

	// 缓冲区满时直接绘制
	if (count_ == total_)
	{
		draw();
	}
}

void BorderDrawer::draw()
{
	// 解除缓冲区映射
	if (buf_)
	{
		glUnmapNamedBuffer(buffer_);
		buf_ = nullptr;
	}

	// 绘制
	if (count_)
	{
		glDrawArrays(GL_LINES, 0, count_ * 2);
		count_ = 0;
	}
}

void BorderDrawer::destroy()
{
	// 解除绑定
	if (buf_)
	{
		glUnmapNamedBuffer(buffer_);
		buf_ = nullptr;
	}
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 删除对象
	glDeleteProgram(program_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &buffer_);
}
