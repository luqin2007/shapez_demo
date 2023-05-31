#include "Trash.h"

#include "TrashRenderer.h"

BuildingContext* Trash::build_context(const Vec2I& pos, const Side direction) const
{
	return new BuildingContext(*this, pos, direction);
}

bool Trash::can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool Trash::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool Trash::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                      const BuildingContext& context) const
{
	return true;
}

void Trash::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void Trash::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                  BuildingContext& context) const
{
}

void Trash::update(BuildingContext& context, GameMap& map) const
{
}

void Trash::free_context(BuildingContext* context) const
{
	delete context;
}

const BuildingRenderer& Trash::get_renderer() const
{
	static TrashRenderer renderer;
	return renderer;
}

vector<Vec2I> Trash::all_positions(const Vec2I& pos, Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	return p;
}
