#include "Rotater.h"

#include "ColoredShapes.h"
#include "RotaterRenderer.h"

BuildingContext* Rotater::build_context(const Vec2I& pos, const Side direction) const
{
	return new RotaterContext(*this, pos, direction);
}

bool Rotater::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == opposite(context.direction);
}

bool Rotater::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool Rotater::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                const BuildingContext& context) const
{
	return !cast(context).has_shape_ && side == opposite(context.direction);
}

void Rotater::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void Rotater::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.has_shape_ = true;
	ctx.shapes_ = shape;
	rotate_item(ctx.shapes_);
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

bool Rotater::can_start(const TickableContext& context) const
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

const BuildingRenderer& RotaterCW::get_renderer() const
{
	return RotaterRenderer::cw();
}

const BuildingRenderer& RotaterCCW::get_renderer() const
{
	return RotaterRenderer::ccw();
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
