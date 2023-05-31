#include "Rotater.h"

#include "ColoredShapes.h"
#include "RotaterRenderer.h"

BuildingContext* Rotater::build_context(const Vec2I& pos, const Side direction) const
{
	return new RotaterContext(*this, pos, direction);
}

bool Rotater::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool Rotater::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool Rotater::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                        const BuildingContext& context) const
{
	return !cast(context).has_shape_ && side == -context.direction;
}

void Rotater::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void Rotater::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                    BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_shape_ = true;
	ctx.shapes_ = shape;
}

void Rotater::free_context(BuildingContext* context) const
{
	delete static_cast<RotaterContext*>(context);
}

vector<Vec2I> Rotater::all_positions(const Vec2I& pos, Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	return p;
}

bool Rotater::can_start(TickableContext& context, const GameMap& map) const
{
	return cast(context).has_shape_;
}

bool Rotater::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (send_shape(context.pos, context.direction, cast(context).shapes_, map))
	{
		cast(context).has_shape_ = false;
		return true;
	}
	return false;
}

bool Rotater::on_finished(TickableContext& context, const GameMap& map) const
{
	return on_blocking(context, map);
}

const BuildingRenderer& RotaterCW::get_renderer() const
{
	static RotaterCWRenderer renderer;
	return renderer;
}

const BuildingRenderer& RotaterCCW::get_renderer() const
{
	static RotaterCCWRenderer renderer;
	return renderer;
}

const Rotater& Rotaters::cw()
{
	static RotaterCW cw;
	static RotaterCCW ccw;
	cw.next_variant = &ccw;
	ccw.next_variant = &cw;
	return cw;
}

const Rotater& Rotaters::ccw()
{
	return *dynamic_cast<const Rotater*>(cw().next_variant);
}
