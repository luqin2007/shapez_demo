#include "Mixer.h"

#include "GameLogic.h"
#include "MixerRenderer.h"

BuildingContext* Mixer::build_context(const Vec2I& pos, const Side direction) const
{
	return new MixerContext{ *this, pos, direction };
}

bool Mixer::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool Mixer::can_receive_dye(const Color color, const Vec2I& pos, Side side,
                                    const BuildingContext& context) const
{
	auto& ctx = cast(context);
	return pos == context.pos
		       // Left
		       ? ctx.color1_ == Color::uncolored && color | ctx.color2_
		       // Right
		       : ctx.color2_ == Color::uncolored && color | ctx.color1_;
}

bool Mixer::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                      const BuildingContext& context) const
{
	return false;
}

void Mixer::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	(pos == context.pos ? cast(context).color1_ : cast(context).color2_) = color;
}

void Mixer::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	BuildingContext& context) const
{
}

void Mixer::free_context(BuildingContext* context) const
{
	delete static_cast<MixerContext*>(context);
}

const BuildingRenderer& Mixer::get_renderer() const
{
	static MixerRenderer renderer;
	return renderer;
}

vector<Vec2I> Mixer::all_positions(const Vec2I& pos, const Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	p.push_back(pos + ++direction);
	return p;
}

bool Mixer::can_start(TickableContext& context, const GameMap& map) const
{
	const auto& ctx = cast(context);
	return ctx.color1_ != Color::uncolored && ctx.color2_ != Color::uncolored;
}

bool Mixer::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		send_dye(context.pos, context.direction, ctx.color1_, map))
	{
		ctx.color1_ = Color::uncolored;
		ctx.color2_ = Color::uncolored;
		return true;
	}
	return false;
}

bool Mixer::on_finished(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);
	ctx.color1_ = ctx.color1_ + ctx.color2_;
	return on_blocking(context, map);
}
