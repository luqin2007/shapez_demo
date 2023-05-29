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

bool GameMap::set_building(const int x, const int y, const Building* building, const Side direction)
{
	if (const auto pos = Vec2I{x, y};
		Building::can_place(pos, building->size, direction, this))
	{
		BuildingContext* ctx = building->build_context(pos, direction);
		for (const auto& p : Building::all_positions(pos, building->size, direction))
			buildings_[p.x][p.y] = ctx;

		building->on_placed(*ctx);

		return true;
	}

	return false;
}

BuildingContext* GameMap::get_building(const int x, const int y) const
{
	return buildings_[x][y];
}

void GameMap::remove_building(const int x, const int y)
{
	if (buildings_[x][y])
	{
		BuildingContext* ctx = buildings_[x][y];
		// 清除记录
		for (const auto& pos : Building::all_positions(ctx->pos, ctx->building.size, ctx->direction))
		{
			buildings_[pos.x][pos.y] = nullptr;
		}
		// 释放资源
		ctx->building.free_context(ctx);
	}
}
