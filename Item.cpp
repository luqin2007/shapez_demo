#include "Item.h"

const Item Item::EMPTY = Item();

DyeItem DyeItem::operator+(const DyeItem& o) const
{
	return DyeItem(color + o.color);
}

ColoredPart ColoredPart::colored(const Color& o) const
{
	return {part, o};
}

ShapeItem ShapeItem::roll() const
{
	return {up_right, down_right, up_left, down_left};
}

ShapeItem ShapeItem::colored(DyeItem& dye) const
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
