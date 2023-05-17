#pragma once

#include <vector>
#include <cmath>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "Common.h"
#include "AbstractDrawer.h"

using std::vector;
using std::max;

class FontDrawer : public AbstractDrawer
{
public:
	explicit FontDrawer(path path): font_path_(std::move(path)), ft_(nullptr), texture_id_(0)
	{
	}

	void initialize();

	void draw(const string& str, int font_size, float x, float y,
	          float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

	void destroy() const;

private:
	const path font_path_;

	FT_Library ft_;

	int texture_id_;
	GLuint texture_ = 0;
};
