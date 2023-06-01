#include "ColoredShapes.h"

#include "TextureDrawer.h"

ColoredShapes ColoredShapes::from_resource(const ResourceType type)
{
	if (type == ResourceType::shape_star)
	{
		return {
			{Color::uncolored, Shape::star},
			{Color::uncolored, Shape::star},
			{Color::uncolored, Shape::star},
			{Color::uncolored, Shape::star},
		};
	}
	if (type == ResourceType::shape_rect)
	{
		return {
			{Color::uncolored, Shape::rect},
			{Color::uncolored, Shape::rect},
			{Color::uncolored, Shape::rect},
			{Color::uncolored, Shape::rect},
		};
	}
	if (type == ResourceType::shape_circle)
	{
		return {
			{Color::uncolored, Shape::fan},
			{Color::uncolored, Shape::fan},
			{Color::uncolored, Shape::fan},
			{Color::uncolored, Shape::fan},
		};
	}
	return {
		{Color::uncolored, Shape::none},
		{Color::uncolored, Shape::none},
		{Color::uncolored, Shape::none},
		{Color::uncolored, Shape::none},
	};
}

void ColoredShapes::operator++()
{
	const auto tmp = down_right;
	down_right = up_right;
	up_right = up_left;
	up_left = down_left;
	down_left = tmp;
}

void ColoredShapes::operator--()
{
	const auto tmp = down_right;
	down_right = down_left;
	down_left = up_left;
	up_left = up_right;
	up_right = tmp;
}

bool ColoredShapes::operator|(const Color color) const
{
	return up_left.first | color && up_right.first | color && down_left.first | color && down_right.first | color;
}

bool ColoredShapes::operator==(const ColoredShapes& item) const
{
	return item.up_left == up_left && item.up_right == up_right
		&& item.down_left == down_left && item.down_right == down_right;
}

void ColoredShapes::draw(const Atlas& atlas, TextureDrawer& drawer, const float x0, const float y0,
                         const float x1, const float y1, const Side direction) const
{
	if (up_left == up_right && up_left == down_left && up_left == down_right)
	{
		if (string name;
			get_draw_name(name, up_left))
		{
			drawer.push(x0, y0, x1, y1, atlas, name, direction);
		}
	}
	else
	{
		const float xc = (x0 + x1) / 2;
		const float yc = (y0 + y1) / 2;

		// 左上角
		if (string name;
			get_draw_name(name, up_left))
		{
			name.append("_lt");
			drawer.push(x0, y0, xc, yc, atlas, name, direction);
		}
		// 右上角
		if (string name;
			get_draw_name(name, up_right))
		{
			name.append("_rt");
			drawer.push(xc, y0, x1, yc, atlas, name, direction);
		}
		// 左下角
		if (string name;
			get_draw_name(name, down_left))
		{
			name.append("_lb");
			drawer.push(x0, yc, xc, y1, atlas, name, direction);
		}
		// 右下角
		if (string name;
			get_draw_name(name, down_right))
		{
			name.append("_rb");
			drawer.push(xc, yc, x1, y1, atlas, name, direction);
		}
	}
}

bool ColoredShapes::get_draw_name(string& name, const pair<Color, Shape>& part)
{
	switch (part.second)
	{
	case Shape::fan:
		name.append("circle_");
		break;
	case Shape::rect:
		name.append("rect_");
		break;
	case Shape::star:
		name.append("star_");
		break;
	default:
		return false;
	}

	name.append(color_icon(part.first));
	return true;
}
