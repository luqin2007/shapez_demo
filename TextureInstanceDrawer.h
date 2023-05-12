#pragma once

#include <glad/glad.h>

#include "Common.h"
#include "AbstractDrawer.h"

class TextureInstanceDrawer : public AbstractDrawer
{
public:
	TextureInstanceDrawer(const int count) : total_(count)
	{
	}

	void initialize(GLuint index);

	void begin() const;

	void tex(GLint tex);

	void alpha(GLfloat alpha);

	void push(float x0, float y0, float x1, float y1, float u, float v, float w, float h);

	void draw();

	void destroy();

private:
	const int total_;
	int count_ = 0;
	GLint tex_ = 0;
	GLfloat alpha_ = 0;
	GLuint vao_;
	GLuint vertices_, indices_, v_indices_;
	float* buf_vertices_ = nullptr;
	int* buf_indices_ = nullptr;
};
