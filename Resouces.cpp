#include <iostream>

#include "resouces.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Text::~Text()
{
	if (str)
	{
		delete[] str;
		str = nullptr;
	}
}

Image::~Image()
{
	if (data)
	{
		stbi_image_free(data);
		data = nullptr;
	}
}

Text read_text(const path& p)
{
	Text text;

	// 校验路径
	using namespace std::filesystem;
	if (!is_regular_file(p))
	{
		std::cerr << "File " << p.string() << " is not a regular file." << endl;
		return text;
	}

	// 按字节读文件
	fstream fs;
	fs.open(p);
	text << file_size(p);
	while (!fs.eof())
	{
		text << fs.get();
	}
	text.end();
	fs.close();
	return text;
}

Image load_image(const path& p)
{
	Image img = {};

	using namespace std::filesystem;
	if (!is_regular_file(p))
	{
		std::cerr << "File " << p.string() << " is not a regular file." << endl;
		return img;
	}

	stbi_set_flip_vertically_on_load(true);
	img.data = stbi_load(p.string().c_str(), &img.width, &img.height, &img.channels, 4);
	return img;
}
