#pragma once

#include <cstdarg>
#include <string>
#include <functional>

#include "Common.h"
#include "Item.h"

using std::string;
using std::function;

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
	const function<Item()> create_item;

	const string name;

	bool operator==(const ResourceType& o) const
	{
		return this == &o;
	}

private:
	ResourceType(const bool is_color, const bool is_shape, string name, const function<Item()>& create_item)
		: is_color(is_color), is_shape(is_shape), create_item(create_item), name(std::move(name))
	{
	}
};

class GameMap
{
public:
	// 屏幕中点对应第 center.x 行，第 center.y 列
	vec2 center{CELL_COUNT / 2.0f, CELL_COUNT / 2.0f};

	float cell_size = 100;

	GameMap();

	void initialize(long long seed);

	void set_resource(int x, int y, const ResourceType& type);

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
	const ResourceType* resources_[CELL_COUNT][CELL_COUNT]{};
	BuildingContext* buildings_[CELL_COUNT][CELL_COUNT]{};
};
