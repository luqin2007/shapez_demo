#include "BuildingTrash.h"

BuildingContext* BuildingTrash::build_context(const Vec2I& pos, const Side direction) const
{
	return new BuildingContext(*this, pos, direction);
}

bool BuildingTrash::can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool BuildingTrash::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool BuildingTrash::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                      const BuildingContext& context) const
{
	return true;
}

void BuildingTrash::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void BuildingTrash::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                  BuildingContext& context) const
{
}

void BuildingTrash::update(BuildingContext& context, GameMap& map) const
{
}

void BuildingTrash::free_context(BuildingContext* context) const
{
	delete context;
}
