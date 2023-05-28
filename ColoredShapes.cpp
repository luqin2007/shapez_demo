#include "ColoredShapes.h"

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
