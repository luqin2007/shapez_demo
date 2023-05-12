#include "GameMap.h"

const ResourceType ResourceType::EMPTY = ResourceType(false, false, "", []() { return Item::EMPTY; });
const ResourceType ResourceType::SHAPE_STAR = ResourceType(false, true, "star_uncolored.png", []()
{
	return ShapeItem{ColoredPart{Part::STAR, Color::uncolored}};
});
const ResourceType ResourceType::SHAPE_RECT = ResourceType(false, true, "rect_uncolored.png", []()
{
	return ShapeItem{ColoredPart{Part::RECT, Color::uncolored}};
});
const ResourceType ResourceType::SHAPE_CIRCLE = ResourceType(false, true, "circle_uncolored.png", []()
{
	return ShapeItem{ColoredPart{Part::FAN, Color::uncolored}};
});
const ResourceType ResourceType::COLOR_BLUE = ResourceType(true, false, "blue.png", []()
{
	return DyeItem{Color::blue};
});
const ResourceType ResourceType::COLOR_YELLOW = ResourceType(true, false, "yellow.png", []()
{
	return DyeItem{Color::yellow};
});
const ResourceType ResourceType::COLOR_RED = ResourceType(true, false, "red.png", []()
{
	return DyeItem{Color::red};
});

GameMap::GameMap()
{
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			resources_[i][j] = &ResourceType::EMPTY;
			buildings_[i][j] = nullptr;
		}
	}
}

void GameMap::initialize(long long seed)
{
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		set_resource(0, i, ResourceType::SHAPE_CIRCLE);
		set_resource(1, i, ResourceType::SHAPE_RECT);
		set_resource(2, i, ResourceType::SHAPE_STAR);
		set_resource(3, i, ResourceType::COLOR_RED);
		set_resource(4, i, ResourceType::COLOR_BLUE);
		set_resource(5, i, ResourceType::COLOR_YELLOW);
	}
}

void GameMap::set_resource(const int x, const int y, const ResourceType& type)
{
	resources_[x][y] = &type;
}

const ResourceType& GameMap::get_resource(const int x, const int y) const
{
	return *resources_[x][y];
}

void GameMap::set_building(BuildingContext* context, int count, ...)
{
	va_list list;
	va_start(list, count);
	while (count--)
	{
		const ivec2 p = va_arg(list, ivec2);
		buildings_[p.x][p.y] = context;
	}
	va_end(list);
}

void GameMap::set_building(BuildingContext* context, const ivec2 pos)
{
	buildings_[pos.x][pos.y] = context;
}

BuildingContext* GameMap::get_building(const int x, const int y) const
{
	return buildings_[x][y];
}
