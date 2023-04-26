#include "GameMap.h"

GameMap::GameMap()
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			resources[i][j] = ResourceType::EMPTY;
			buildings[i][j] = nullptr;
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

void GameMap::set_resource(int x, int y, ResourceType type)
{
	resources[x][y] = type;
}

ResourceType GameMap::get_resource(int x, int y) const
{
	return resources[x][y];
}

void GameMap::set_building(BuildingContext* context, int count, ...)
{
	va_list list;
	va_start(list, count);
	while (count--)
	{
		ivec2 p = va_arg(list, ivec2);
		buildings[p.x][p.y] = context;
	}
	va_end(list);
}

void GameMap::set_building(BuildingContext* context, ivec2 pos)
{
	buildings[pos.x][pos.y] = context;
}

BuildingContext* GameMap::get_building(int x, int y) const
{
	return buildings[x][y];
}
