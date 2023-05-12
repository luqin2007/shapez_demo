#pragma once

#include <glad/glad.h>

#include "Common.h"
#include "AbstractDrawer.h"

class BorderDrawer: public AbstractDrawer
{
public:
	BorderDrawer(const int count) : total_(count)
	{
	}

	void initialize();

	void begin() const;
	
	void push(float x0, float y0, float x1, float y1);

	void draw();

	void destroy();

private:
	const int total_;
	int count_ = 0;
	GLuint vao_, buffer_;
	float* buf_ = nullptr;
};
