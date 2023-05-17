#include "TextureInstanceDrawer.h"

void TextureInstanceDrawer::initialize()
{
	cout << " Create texture buffers" << endl;
	glCreateBuffers(1, &buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, total_ * 8 * sizeof(float), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	glCreateBuffers(1, &indices_);
	glBindBuffer(GL_ARRAY_BUFFER, indices_);
	glNamedBufferStorage(indices_, total_ * 4 * sizeof(int), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	create_program(program_, "tex_instance.vert", "tex_alpha.frag");
	glUseProgram(program_);
	glUniform1i(1, 0);
	glUniform1f(2, 1);

	cout << " Create tex vertex object..." << endl;
	constexpr GLsizei v_size = 8 * sizeof(float);
	glCreateVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	bind_indices();
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, v_size, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, v_size, reinterpret_cast<const void*>(4 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 6);
	glBindBuffer(GL_ARRAY_BUFFER, indices_);
	glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, 0);
}

void TextureInstanceDrawer::begin() const
{
	glUseProgram(program_);
	glBindVertexArray(vao_);
}

void TextureInstanceDrawer::tex(const GLint tex)
{
	if (tex != tex_)
	{
		draw();
		tex_ = tex;
		glUniform1i(1, tex);
	}
}

void TextureInstanceDrawer::alpha(const GLfloat alpha)
{
	if (fneq(alpha, alpha_))
	{
		draw();
		alpha_ = alpha;
		glUniform1f(2, alpha);
	}
}

void TextureInstanceDrawer::push(const float x0, const float y0, const float x1, const float y1,
                                 const float u, const float v, const float w, const float h)
{
	if (!buf_vertices_)
	{
		buf_vertices_ = static_cast<float*>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
		buf_indices_ = static_cast<int*>(glMapNamedBuffer(indices_, GL_WRITE_ONLY));
		count_ = 0;
	}

	*buf_vertices_++ = x0;
	*buf_vertices_++ = y0;
	*buf_vertices_++ = u;
	*buf_vertices_++ = v;
	*buf_vertices_++ = x1;
	*buf_vertices_++ = y1;
	*buf_vertices_++ = u + w;
	*buf_vertices_++ = v + h;
	*buf_indices_++ = 0;
	*buf_indices_++ = 1;
	*buf_indices_++ = 2;
	*buf_indices_++ = 3;
	count_++;

	if (count_ == total_)
	{
		draw();
	}
}

void TextureInstanceDrawer::draw()
{
	if (buf_vertices_)
	{
		glUnmapNamedBuffer(buffer_);
		glUnmapNamedBuffer(indices_);
		buf_vertices_ = nullptr;
		buf_indices_ = nullptr;
	}
	if (count_)
	{
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, count_);
		count_ = 0;
	}
}

void TextureInstanceDrawer::destroy()
{
	if (buf_vertices_)
	{
		glUnmapNamedBuffer(buffer_);
		glUnmapNamedBuffer(indices_);
		buf_vertices_ = nullptr;
		buf_indices_ = nullptr;
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);

	glDeleteProgram(program_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &buffer_);
	glDeleteBuffers(1, &indices_);
}
