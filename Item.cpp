#include "Item.h"

const Item Item::EMPTY = Item();

DyeItem DyeItem::operator+(const DyeItem& o) const
{
	return DyeItem(color + o.color);
}

bool DyeItem::operator==(const Item& item) const
{
	return typeid(item).name() == typeid(DyeItem).name() && dynamic_cast<const DyeItem&>(item).color == this->color;
}

ColoredPart ColoredPart::colored(const Color& o) const
{
	return {part, o};
}

bool ColoredPart::operator==(const ColoredPart& o) const
{
	return color == o.color && part == o.part;
}

ShapeItem ShapeItem::roll() const
{
	return {up_right, down_right, up_left, down_left};
}

ShapeItem ShapeItem::colored(const DyeItem& dye) const
{
	return {
		down_right.colored(dye.color), down_left.colored(dye.color),
		up_right.colored(dye.color), up_left.colored(dye.color)
	};
}

pair<ShapeItem, ShapeItem> ShapeItem::cut() const
{
	return {
		{{Part::NONE, Color::uncolored}, down_left, {Part::NONE, Color::uncolored}, up_right},
		{down_right, {Part::NONE, Color::uncolored}, up_right, {Part::NONE, Color::uncolored}}
	};
}

bool ShapeItem::operator==(const Item& item) const
{
	if (typeid(item).name() == typeid(ShapeItem).name())
	{
		const auto& o = dynamic_cast<const ShapeItem&>(item);
		return (*this)[0] == o[0] && (*this)[1] == o[1] && (*this)[2] == o[2] && (*this)[3] == o[3];
	}

	return false;
}

ColoredPart ShapeItem::operator[](int idx) const
{
	switch (idx)
	{
	case 0: return up_left;
	case 1: return up_right;
	case 2: return down_left;
	default: return down_right;
	}
}
