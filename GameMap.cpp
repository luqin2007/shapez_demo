#include "GameMap.h"

const ResourceType ResourceType::EMPTY = ResourceType(false, false, "");
const ResourceType ResourceType::SHAPE_STAR = ResourceType(false, true, "star.png");
const ResourceType ResourceType::SHAPE_RECT = ResourceType(false, true, "rect.png");
const ResourceType ResourceType::SHAPE_CIRCLE = ResourceType(false, true, "circle.png");
const ResourceType ResourceType::COLOR_BLUE = ResourceType(true, false, "blue.png");
const ResourceType ResourceType::COLOR_YELLOW = ResourceType(true, false, "yellow.png");
const ResourceType ResourceType::COLOR_RED = ResourceType(true, false, "red.png");

GameMap::GameMap()
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			resources_[i][j] = &ResourceType::EMPTY;
			buildings_[i][j] = nullptr;
		}
	}
}

void GameMap::initialize(long long seed)
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			set_resource(i, j, ResourceType::SHAPE_CIRCLE);
			set_resource(99 - i, j, ResourceType::SHAPE_RECT);
			set_resource(i, 99 - j, ResourceType::SHAPE_STAR);
			set_resource(99 - i, 99 - j, ResourceType::COLOR_RED);
		}
		set_resource(40 + i * 2, 0, ResourceType::COLOR_BLUE);
		set_resource(40 + i * 2 + 1, 0, ResourceType::COLOR_BLUE);
		set_resource(40 + i * 2, 99, ResourceType::COLOR_BLUE);
		set_resource(40 + i * 2 + 1, 99, ResourceType::COLOR_BLUE);
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
