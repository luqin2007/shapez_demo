#pragma once
#include <string>

static std::string icon_names[] =
{
	"",
	"circle_uncolored.png",
	"rect_uncolored.png",
	"star_uncolored.png",
	"red.png",
	"blue.png",
	"green.png"
};

/**
 * \brief 地图资源
 */
enum class ResourceType
{
	none = 0,
	shape_circle,
	shape_rect,
	shape_star,
	color_red,
	color_blue,
	color_green
};

inline bool is_color(const ResourceType res)
{
	return res == ResourceType::color_red || res == ResourceType::color_blue || res == ResourceType::color_green;
}

inline bool is_shape(const ResourceType res)
{
	return res == ResourceType::shape_circle || res == ResourceType::shape_rect || res == ResourceType::shape_star;
}

/**
 * \brief 获取资源对应材质图标
 * \param type 资源类型
 * \return 材质名
 */
inline std::string& resource_icon(ResourceType type)
{
	return icon_names[static_cast<int>(type)];
}
