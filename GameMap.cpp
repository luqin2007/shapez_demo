#include "GameMap.h"

#include "Building.h"
#include "BuildingContext.h"
#include "Hub.h"

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
	// 初始化资源
	for (int i = 0; i < CELL_COUNT; ++i)
	{
		resources_[0 + 70][i] = ResourceType::shape_circle;
		resources_[1 + 70][i] = ResourceType::shape_rect;
		resources_[2 + 70][i] = ResourceType::shape_star;
		resources_[3 + 70][i] = ResourceType::color_red;
		resources_[4 + 70][i] = ResourceType::color_blue;
		resources_[5 + 70][i] = ResourceType::color_green;

		resources_[CELL_COUNT - 1 - 70][i] = ResourceType::shape_circle;
		resources_[CELL_COUNT - 2 - 70][i] = ResourceType::shape_rect;
		resources_[CELL_COUNT - 3 - 70][i] = ResourceType::shape_star;
		resources_[CELL_COUNT - 4 - 70][i] = ResourceType::color_red;
		resources_[CELL_COUNT - 5 - 70][i] = ResourceType::color_blue;
		resources_[CELL_COUNT - 6 - 70][i] = ResourceType::color_green;
	}

	// 初始化 hub
	set_building(CELL_COUNT / 2 - 2, CELL_COUNT / 2 - 2, &Hub::instance(), Side::up);
}

ResourceType GameMap::get_resource(const int x, const int y) const
{
	if (x >= 0 && x < CELL_COUNT && y >= 0 && y < CELL_COUNT)
	{
		return resources_[x][y];
	}

	return ResourceType::none;
}

bool GameMap::set_building(const int x, const int y, const Building* building, const Side direction)
{
	if (x >= 0 && x < CELL_COUNT && y >= 0 && y < CELL_COUNT)
	{
		if (const auto pos = Vec2I{x, y};
			building->can_place(pos, direction, *this))
		{
			BuildingContext* ctx = building->build_context(pos, direction);
			for (const auto& p : building->all_positions(pos, direction))
				buildings_[p.x][p.y] = ctx;

			building->on_placed(*ctx);

			return true;
		}
	}
	return false;
}

BuildingContext* GameMap::get_building(const int x, const int y) const
{
	if (x >= 0 && x < CELL_COUNT && y >= 0 && y < CELL_COUNT)
	{
		return buildings_[x][y];
	}

	return nullptr;
}

void GameMap::remove_building(const int x, const int y)
{
	if (x >= 0 && x < CELL_COUNT && y >= 0 && y < CELL_COUNT
		// 不能移除任务中心！！！
		&& buildings_[x][y] && buildings_[x][y]->building != Hub::instance())
	{
		BuildingContext* ctx = buildings_[x][y];
		// 清除记录
		for (const auto& pos : ctx->building.all_positions(ctx->pos, ctx->direction))
		{
			buildings_[pos.x][pos.y] = nullptr;
		}
		// 释放资源
		ctx->building.free_context(ctx);
	}
}
