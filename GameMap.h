#pragma once

#include <cstdarg>

#include "Common.h"

class BuildingContext;

enum class ResourceType
{
	EMPTY,
	SHAPE_CIRCLE,
	SHAPE_RECT,
	SHAPE_STAR,
	COLOR_RED,
	COLOR_BLUE,
	COLOR_YELLOW
};

class GameMap
{
public:
	GameMap();

	void initialize(long long seed);

	void set_resource(int x, int y, ResourceType type);

	void set_resource(ivec2 pos, ResourceType type)
	{
		set_resource(pos.x, pos.y, type);
	}

	ResourceType get_resource(int x, int y) const;

	ResourceType get_resource(const ivec2& pos) const
	{
		return get_resource(pos.x, pos.y);
	};

	void set_building(BuildingContext* context, int count, ...);

	void set_building(BuildingContext* context, ivec2 pos);

	BuildingContext* get_building(int x, int y) const;

	BuildingContext* get_building(const ivec2& pos) const
	{
		return get_building(pos.x, pos.y);
	}

private:
	ResourceType resources[100][100]{};
	BuildingContext* buildings[100][100]{};
};
