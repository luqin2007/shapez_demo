#pragma once

#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <exception>

#include <glad/glad.h>

#include "Resouces.h"
#include "Common.h"

using std::map;
using std::string;
using std::filesystem::path;
using std::cout;
using std::endl;
using std::exception;

class Atlas
{
public:
	Atlas(const float width, const float height, const int cell_width, const int cell_height, const bool m4 = false):
		width_(width), height_(height), cell_width_(cell_width), cell_height_(cell_height),
		count_per_row_(static_cast<int>(width) / cell_width), count_per_col_(static_cast<int>(height) / cell_height),
		index_(next_texture_id()), m4_(m4)
	{
	}

	Atlas(const float size, const int cell_size, const bool m4 = false) : Atlas(size, size, cell_size, cell_size, m4)
	{
	}

	void initialize();
	
	void destroy() const;

	operator GLint() const
	{
		return index_;
	}

	Atlas& operator<<(const path& p);

	const UV& operator[](const string& name);

private:
	const float width_, height_;
	const int cell_width_, cell_height_, count_per_row_, count_per_col_, index_;
	const bool m4_;
	map<string, UV> atlas_;

	int row_ = 0, col_ = 0;

	GLuint texture_ = 0;
};
