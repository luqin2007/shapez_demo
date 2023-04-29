#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

using std::string;
using std::filesystem::path;
using std::filesystem::current_path;
using std::fstream;
using std::cerr;
using std::endl;

struct Text
{
	uintmax_t len = 0;
	char* str = nullptr;

	~Text();

	void operator<<(uintmax_t size)
	{
		str = new char[size + 1];
		len = 0;
	}

	void operator<<(int ch)
	{
		str[len++] = (char)ch;
	}

	void end() const
	{
		str[len - 1] = '\0';
	}
};

struct Image
{
	int width, height, channels;

	unsigned char* data;

	~Image();
};

namespace Resouces
{
	path root();

	Text read_text(const path& p);

	Image load_image(const path& p);
}
