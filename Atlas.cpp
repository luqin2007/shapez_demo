#include "Atlas.h"

#include "resouces.h"
#include "ft2build.h"
#include FT_FREETYPE_H

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
	cout << "  Loading image " << p.string() << endl;
	const auto [width, height, channels, data] = load_image(p);
	put_image(width, height, GL_RGBA, p.filename().string().c_str(), data);
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

Atlas& Atlas::operator<<(const char* text)
{
	cout << "  Loading string " << text << endl;
	// 初始化 FreeType
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		cerr << "初始化 FreeType 失败" << endl;
		return *this;
	}

	FT_Face face;
	if (const path font = ROOT / "font" / "MicrosoftYaHei.ttf";
		FT_New_Face(ft, font.string().c_str(), 0, &face))
	{
		cerr << "创建 FTFace 失败" << endl;
		return *this;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);

	// 添加字形
	int p = 0;
	char ch;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	while ((ch = text[p++]))
	{
		if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
		{
			cerr << "创建字形 " << ch << " 失败" << endl;
			continue;
		}

		const char cc[2] = {ch, '\0'};
		put_image(face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, &cc[0], face->glyph->bitmap.buffer);
		chars_[ch] = {
			face->glyph->bitmap.width, face->glyph->bitmap.rows,
			face->glyph->bitmap_left, face->glyph->bitmap_top,
			static_cast<GLuint>(face->glyph->advance.x)
		};
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

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

void Atlas::put_image(const int width, const int height, const GLenum format, const char* name, const void* image)
{
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
	glTextureSubImage2D(texture_, 0, xx, yy, width, height, format, GL_UNSIGNED_BYTE, image);
	const string filename = name;

	// 计算图片位置，生成 uv 数据
	if (atlas_.contains(filename))
	{
		char s[300];
		sprintf_s(s, 300, "重复的纹理名: %s", filename.c_str());
		throw exception(s);
	}
	const Rect uv = {xx / width_, yy / height_, width / width_, height / height_};
	atlas_[filename] = uv;

	// 检查是否需要从中间拆分
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
}
