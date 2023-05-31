#include "Atlas.h"

#include "resouces.h"
#include "common.h"

#include <cstring>

Atlas::Atlas(const float width, const float height, const int cell_width, const int cell_height):
	width_(width), height_(height), cell_width_(cell_width), cell_height_(cell_height),
	col_count_(static_cast<int>(width) / cell_width), row_count_(static_cast<int>(height) / cell_height),
	index_(image_id_++)
{
	is_space_used_ = new bool*[row_count_];
	for (int i = 0; i < row_count_; ++i)
	{
		is_space_used_[i] = new bool[col_count_];
		memset(is_space_used_[i], 0, col_count_ * sizeof(bool));
	}
}

Atlas& Atlas::initialize()
{
	cout << " Create texture" << index_
		<< " alias(" << width_ << "x" << height_ << ", cell=" << cell_width_ << "x" << cell_height_ << ")..." << endl;
	glActiveTexture(index_ + GL_TEXTURE0);
	glCreateTextures(GL_TEXTURE_2D, 1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(width_), static_cast<GLsizei>(height_), 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, nullptr);
	return *this;
}

void Atlas::destroy() const
{
	glActiveTexture(index_ + GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture_);
}

Atlas& Atlas::operator<<(const path& p)
{
	cout << "  Loading image " << p.string();

	// 读取图片，计算需要的单元数
	const auto [width, height, channels, data] = load_image(p);
	const int use_col = ceil(static_cast<float>(width) / cell_width_);
	const int use_row = ceil(static_cast<float>(height) / cell_height_);
	best_cell_width_ = bcd(best_cell_width_, width);
	best_cell_height_ = bcd(best_cell_height_, height);

	// 遍历所有空间，查询可用空间
	int row = -1, col = -1;
	for (int r = 0; row == -1 && r < row_count_ - use_row; ++r)
	{
		for (int c = 0; row == -1 && c < col_count_ - use_col; ++c)
		{
			bool can_use = true;
			for (int i = 0; can_use && i < use_row; ++i)
			{
				for (int j = 0; can_use && j < use_col; ++j)
				{
					can_use = !is_space_used_[r + i][c + j];
					if (!can_use)
					{
						c += j;
					}
				}
			}

			// 可用并填充
			if (can_use)
			{
				row = r;
				col = c;
				for (int i = 0; i < use_row; ++i)
				{
					for (int j = 0; j < use_col; ++j)
					{
						is_space_used_[r + i][c + j] = true;
					}
				}
			}
		}
	}
	if (row == -1)
	{
		throw exception("纹理集过小");
	}

	// 计算行、列偏移
	const GLint xx = col * cell_width_;
	const GLint yy = row * cell_height_;

	// 加载图片
	glTextureSubImage2D(texture_, 0, xx, yy, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	const string filename = p.filename().string();

	// 计算图片位置，生成 uv 数据
	if (atlas_.contains(filename))
	{
		char s[300];
		sprintf_s(s, 300, "重复的纹理名: %s", filename.c_str());
		throw exception(s);
	}
	const Rect uv = {xx / width_, yy / height_, width / width_, height / height_};
	atlas_[filename] = uv;
	cout << " [" << uv.u << ", " << uv.v << ", " << uv.w << ", " << uv.h << "]" << endl;
	if (m4_)
	{
		const float x0 = xx, x1 = x0 + width / 2.0f;
		const float y0 = yy, y1 = y0 + height / 2.0f;
		atlas_[filename + "_lt"] = {x0 / width_, y0 / height_, width / 2.0f / width_, height / 2.0f / height_};
		atlas_[filename + "_rt"] = {x1 / width_, y0 / height_, width / 2.0f / width_, height / 2.0f / height_};
		atlas_[filename + "_lb"] = {x0 / width_, y1 / height_, width / 2.0f / width_, height / 2.0f / height_};
		atlas_[filename + "_rb"] = {x1 / width_, y1 / height_, width / 2.0f / width_, height / 2.0f / height_};
	}

	// 检查 .9 配置
	if (has_d9_)
	{
		dot9s_[filename] = d9_;
		has_d9_ = false;
	}
	return *this;
}

Atlas& Atlas::operator<<(const Action action)
{
	switch (action)
	{
	case Action::m4:
		m4_ = true;
		break;
	case Action::mipmap:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		break;
	case Action::finished:
		for (int i = 0; i < row_count_; ++i)
		{
			delete[] is_space_used_[i];
		}
		delete[] is_space_used_;

		if (best_cell_width_ != cell_width_ || best_cell_height_ != cell_height_)
		{
			cout << "  Warn: best cell size is " << best_cell_width_ << " x " << best_cell_height_ << endl;
		}
		break;
	}

	return *this;
}

Atlas& Atlas::operator<<(const dot9 data)
{
	has_d9_ = true;
	d9_ = data;
	return *this;
}

Rect& Atlas::operator[](const string& name)
{
	return atlas_[name];
}

Rect& Atlas::operator[](const char* name)
{
	return atlas_[name];
}

int Atlas::bcd(int a, int b)
{
	if (b > a) std::swap(a, b);
	if (b == 0 || a % b == 0) return a;
	return bcd(b, a % b);
}
