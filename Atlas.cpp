#include "Atlas.h"

void Atlas::initialize()
{
	cout << " Create texture" << index_ << " alias(" << width_ << "x" << height_ << ", cell=" << cell_width_ << "x" <<
		cell_height_ << ")..." <<
		endl;
	glActiveTexture(index_ + GL_TEXTURE0);
	glCreateTextures(GL_TEXTURE_2D, 1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
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

	if (row_ > count_per_col_)
	{
		throw exception("This atlas is too small to accept more texture.");
	}

	const GLint off_x = col_ * cell_width_;
	const GLint off_y = row_ * cell_height_;

	const Image image = Resouces::load_image(p);
	glTextureSubImage2D(texture_, 0, off_x, off_y, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
	const string filename = p.filename().string();
	atlas_[filename] = {off_x / width_, off_y / height_, image.width / width_, image.height / height_};
	if (m4_)
	{
		const float x0 = off_x, x1 = x0 + image.width / 2.0f;
		const float y0 = off_y, y1 = y0 + image.height / 2.0f;
		atlas_[filename + "_lt"] = {x0 / width_, y0 / height_, image.width / 2 / width_, image.height / 2 / height_};
		atlas_[filename + "_rt"] = {x1 / width_, y0 / height_, image.width / 2 / width_, image.height / 2 / height_};
		atlas_[filename + "_lb"] = {x0 / width_, y1 / height_, image.width / 2 / width_, image.height / 2 / height_};
		atlas_[filename + "_rb"] = {x1 / width_, y1 / height_, image.width / 2 / width_, image.height / 2 / height_};
	}

	col_++;
	if (col_ >= count_per_row_)
	{
		col_ = 0;
		row_++;
	}

	return *this;
}

const UV& Atlas::operator[](const string& name)
{
	return atlas_[name];
}
