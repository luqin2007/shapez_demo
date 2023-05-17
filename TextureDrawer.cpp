#include "TextureDrawer.h"

void TextureDrawer::initialize()
{
	cout << " Create texture buffers" << endl;
	glCreateBuffers(1, &buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, total_ * 24 * sizeof(float), 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	create_program(program_, "tex_single.vert", "tex_alpha.frag");
	glUseProgram(program_);
	glUniform1i(1, 0);
	glUniform1f(2, 1.0f);

	cout << " Create tex vertex object..." << endl;
	glCreateVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	bind_indices();
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribDivisor(0, 0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void TextureDrawer::begin() const
{
	glUseProgram(program_);
	glBindVertexArray(vao_);
}

void TextureDrawer::tex(const GLint tex)
{
	if (tex != tex_)
	{
		draw();
		tex_ = tex;
		glUniform1i(1, tex);
	}
}

void TextureDrawer::alpha(const GLfloat alpha)
{
	if (fneq(alpha, alpha_))
	{
		draw();
		alpha_ = alpha;
		glUniform1f(2, alpha);
	}
}

void TextureDrawer::push(const float x0, const float y0, const float x1, const float y1,
                         const float u, const float v, const float w, const float h)
{
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
	*buf_++ = v + h;

	*buf_++ = x1;
	*buf_++ = y0;
	*buf_++ = u + w;
	*buf_++ = v;

	*buf_++ = x0;
	*buf_++ = y1;
	*buf_++ = u;
	*buf_++ = v + h;

	*buf_++ = x1;
	*buf_++ = y1;
	*buf_++ = u + w;
	*buf_++ = v + h;

	*buf_++ = x1;
	*buf_++ = y0;
	*buf_++ = u + w;
	*buf_++ = v;
	
	count_++;
	if (count_ == total_)
	{
		draw();
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);

	glDeleteProgram(program_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &buffer_);
}
