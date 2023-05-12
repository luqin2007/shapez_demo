#include "BorderDrawer.h"

void BorderDrawer::initialize()
{
	create_program(program_, "cell_border.vert", "cell_border.frag");

	cout << " Create cell buffers" << endl;
	glCreateBuffers(1, &buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glNamedBufferStorage(buffer_, total_ * 4 * sizeof(float), 0, GL_MAP_WRITE_BIT | GL_MAP_READ_BIT);

	cout << " Create cell vertex object..." << endl;
	glCreateVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
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

	if (count_ == total_)
	{
		draw();
	}
}

void BorderDrawer::draw()
{
	if (buf_)
	{
		glUnmapNamedBuffer(buffer_);
		buf_ = nullptr;
	}
	if (count_)
	{
		glDrawArrays(GL_LINES, 0, count_ * 2);
		count_ = 0;
	}
}

void BorderDrawer::destroy()
{
	if (buf_)
	{
		glUnmapNamedBuffer(buffer_);
		buf_ = nullptr;
	}
	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteProgram(program_);
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &buffer_);
}
