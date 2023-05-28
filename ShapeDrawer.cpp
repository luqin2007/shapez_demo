#include "ShapeDrawer.h"

void ShapeDrawer::initialize()
{
	// 缓冲区
	glCreateBuffers(1, &buffer_);
	create_program(program_, "only_pos.vert", "uni_color.frag", true);
	glCreateVertexArrays(1, &vao_);

	// 顶点数组对象
	glBindVertexArray(vao_);
	bind_indices();
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, 8 * sizeof(float), nullptr, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ShapeDrawer::rect(const float x0, const float y0, const float x1, const float y1,
                       const float r, const float g, const float b, const float a) const
{
	glUseProgram(program_);
	glBindVertexArray(vao_);

	glUniform4f(1, r, g, b, a);

	auto buf = static_cast<float*>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
	*buf++ = x0;
	*buf++ = y0;
	*buf++ = x0;
	*buf++ = y1;
	*buf++ = x1;
	*buf++ = y1;
	*buf++ = x1;
	*buf   = y0;
	glUnmapNamedBuffer(buffer_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void ShapeDrawer::destroy() const
{
	// 解除绑定
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// 删除对象
	glDeleteProgram(program_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &buffer_);
}
