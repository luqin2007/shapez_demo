#pragma once

#include <cstdarg>
#include <string>

#include "Common.h"

using std::string;

class BuildingContext;

class ResourceType
{
public:
	const static ResourceType EMPTY;
	const static ResourceType SHAPE_CIRCLE;
	const static ResourceType SHAPE_RECT;
	const static ResourceType SHAPE_STAR;
	const static ResourceType COLOR_RED;
	const static ResourceType COLOR_BLUE;
	const static ResourceType COLOR_YELLOW;

	const bool is_color, is_shape;

	const string name;

private:
	ResourceType(const bool is_color, const bool is_shape, string name)
		: is_color(is_color), is_shape(is_shape), name(std::move(name))
	{
	}
};

class GameMap
{
public:
	// 屏幕中点对应第 center.x 行，第 center.y 列
	vec2 center{50, 50};

	float cell_size = 100;

	GameMap();

	void initialize(long long seed);

	void set_resource(int x, int y, const ResourceType& type);

	void set_resource(const ivec2 pos, const ResourceType& type)
	{
		set_resource(pos.x, pos.y, type);
	}

	const ResourceType& get_resource(int x, int y) const;

	const ResourceType& get_resource(const ivec2& pos) const
	{
		return get_resource(pos.x, pos.y);
	}

	void set_building(BuildingContext* context, int count, ...);

	void set_building(BuildingContext* context, ivec2 pos);

	BuildingContext* get_building(int x, int y) const;

	BuildingContext* get_building(const ivec2& pos) const
	{
		return get_building(pos.x, pos.y);
	}

private:
	const ResourceType* resources_[100][100]{};
	BuildingContext* buildings_[100][100]{};
};
