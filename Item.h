#pragma once

#include <utility>
#include <typeinfo>

#include "Common.h"

using std::pair;

enum class Part
{
	RECT,
	FAN,
	STAR,
	NONE
};

class Item
{
public:
	static const Item EMPTY;

	virtual bool operator==(const Item& o) const
	{
		return this == &o;
	}
};

class DyeItem : public Item
{
public:
	const Color& color;

	explicit DyeItem(const Color& color) : color(color)
	{
	}

	DyeItem operator+(const DyeItem& o) const;

	bool operator==(const Item&) const override;
};

class ColoredPart
{
public:
	const Part part;
	const Color& color;

	ColoredPart(Part part, const Color& color) : part(part), color(color)
	{
	}

	ColoredPart(const ColoredPart& p) = default;

	ColoredPart colored(const Color& o) const;

	bool operator==(const ColoredPart&) const;
};

class ShapeItem : public Item
{
public:
	ColoredPart down_right;
	ColoredPart down_left;
	ColoredPart up_right;
	ColoredPart up_left;

	explicit ShapeItem(ColoredPart part) : down_right(part), down_left(part), up_right(part), up_left(part)
	{
	}

	ShapeItem(ColoredPart downRight, ColoredPart downLeft, ColoredPart upRight, ColoredPart upLeft) :
		down_right(downRight), down_left(downLeft), up_right(upRight), up_left(upLeft)
	{
	}

	ShapeItem roll() const;

	ShapeItem colored(const DyeItem& dye) const;

	pair<ShapeItem, ShapeItem> cut() const;

	bool operator==(const Item&) const override;

	ColoredPart operator[](int idx) const;
};
