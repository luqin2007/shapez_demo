#include "Atlas.h"

#include "resouces.h"

void Atlas::initialize()
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

	// 每个单元均已填满
	if (row_ > count_per_col_)
		throw exception("This atlas is too small to accept more texture.");

	// 计算行、列偏移
	const GLint off_x = col_ * cell_width_;
	const GLint off_y = row_ * cell_height_;

	// 加载图片
	const auto [width, height, channels, data] = load_image(p);
	glTextureSubImage2D(texture_, 0, off_x, off_y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	const string filename = p.filename().string();

	// 生成图片位置
	const auto xx = static_cast<float>(off_x), yy = static_cast<float>(off_y);
	const auto ww = static_cast<float>(width), hh = static_cast<float>(height);
	const Rect uv = {xx / width_, yy / height_, ww / width_, hh / height_};
	atlas_[filename] = uv;
	cout << " [" << uv.u << ", " << uv.v << ", " << uv.w << ", " << uv.h << "]" << endl;
	if (m4_)
	{
		const float x0 = xx, x1 = x0 + ww / 2.0f;
		const float y0 = yy, y1 = y0 + hh / 2.0f;
		atlas_[filename + "_lt"] = {x0 / width_, y0 / height_, ww / 2 / width_, hh / 2 / height_};
		atlas_[filename + "_rt"] = {x1 / width_, y0 / height_, ww / 2 / width_, hh / 2 / height_};
		atlas_[filename + "_lb"] = {x0 / width_, y1 / height_, ww / 2 / width_, hh / 2 / height_};
		atlas_[filename + "_rb"] = {x1 / width_, y1 / height_, ww / 2 / width_, hh / 2 / height_};
	}

	col_++;
	if (col_ >= count_per_row_)
	{
		col_ = 0;
		row_++;
	}

	return *this;
}

Atlas& Atlas::operator<<(const bool gen_mipmap)
{
	if (gen_mipmap)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return *this;
}

const Rect& Atlas::operator[](const string& name)
{
	return atlas_[name];
}

const Rect& Atlas::operator[](const char* name)
{
	return atlas_[name];
}
