#include "Building.h"

#include "GameLogic.h"

bool Building::can_place(const ivec2& pos, const Side direction, const GameMap& map) const
{
	ivec2 x0 = pos;
	const Side direction_right = --direction;
	for (int i = 0; i < size.x; ++i)
	{
		ivec2 y0 = x0;
		for (int j = 0; j < size.y; ++j)
		{
			if (map.get_building(i, j)) return false;
			y0 = y0 + direction;
		}
		x0 = x0 + direction_right;
	}
	return true;
}

vector<ivec2> Building::all_positions(const ivec2& pos, Side direction)
{
	vector<ivec2> cells;
	ivec2 x0 = pos;
	for (int i = 0; i < pos.x; ++i)
	{
		ivec2 y0 = x0;
		const Side off = ++direction;
		for (int j = 0; j < pos.y; ++j)
		{
			cells.push_back(y0);
			y0 = y0 + off;
		}
		x0 = x0 + direction;
	}
	return cells;
}
