#include "GameMap.h"

#include "Building.h"
#include "BuildingContext.h"

GameMap::GameMap()
{
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		for (int j = 0; j < CELL_COUNT; ++j)
		{
			resources_[i][j] = ResourceType::none;
			buildings_[i][j] = nullptr;
		}
	}
}

void GameMap::initialize()
{
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		
		resources_[0][i] = ResourceType::shape_circle;
		resources_[1][i] = ResourceType::shape_rect;
		resources_[2][i] = ResourceType::shape_star;
		resources_[3][i] = ResourceType::color_red;
		resources_[4][i] = ResourceType::color_blue;
		resources_[5][i] = ResourceType::color_green;
	}
}

ResourceType GameMap::get_resource(const int x, const int y) const
{
	return resources_[x][y];
}

void GameMap::set_building(BuildingContext* context)
{
	for (const auto& pos : Building::all_positions(context->pos, context->building.size, context->direction))
		buildings_[pos.x][pos.y] = context;
}

BuildingContext* GameMap::get_building(const int x, const int y) const
{
	return buildings_[x][y];
}
