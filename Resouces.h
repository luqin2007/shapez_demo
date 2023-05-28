#pragma once

#include <filesystem>
#include <fstream>
#include <string>

using std::string;
using std::filesystem::path;
using std::filesystem::current_path;
using std::fstream;
using std::endl;

/**
 * \brief 纯文本
 */
struct Text
{
	uintmax_t len = 0;
	char* str = nullptr;

	~Text();

	void operator<<(const uintmax_t size)
	{
		str = new char[size + 1];
		len = 0;
	}

	void operator<<(const int ch)
	{
		str[len++] = static_cast<char>(ch);
	}

	void end() const
	{
		str[len - 1] = '\0';
	}
};

/**
 * \brief 使用 stb_image 读的图片
 */
struct Image
{
	int width, height, channels;

	unsigned char* data;

	~Image();
};

/**
 * \brief 当前路径
 */
#define ROOT (current_path())

/**
 * \brief 读文本
 * \param p 路径
 * \return 文本
 */
Text read_text(const path& p);

/**
 * \brief 读图片
 * \param p 路径
 * \return 图片
 */
Image load_image(const path& p);
