#include "Mixer.h"

#include "GameLogic.h"
#include "MixerRenderer.h"

BuildingContext* Mixer::build_context(const Vec2I& pos, const Side direction) const
{
	return new MixerContext{ *this, pos, direction };
}

bool Mixer::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == opposite(context.direction);
}

bool Mixer::can_receive_dye(const Color color, const Vec2I& pos, Side side,
                                    const BuildingContext& context) const
{
	auto& ctx = cast(context);
	return pos == ctx.left_pos_
		       // Left
		       ? ctx.color_left_ == Color::uncolored && color | ctx.color_right_
		       // Right
		       : ctx.color_right_ == Color::uncolored && color | ctx.color_left_;
}

bool Mixer::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                      const BuildingContext& context) const
{
	return false;
}

void Mixer::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	if (pos == ctx.left_pos_)
	{
		ctx.color_left_ = ctx.color_right_ + color;
	}
	else
	{
		ctx.color_right_ = color;
		if (ctx.color_left_ != Color::uncolored)
		{
			ctx.color_left_ = ctx.color_left_ + color;
		}
	}
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
	p.push_back(pos + ~direction);
	return p;
}

bool Mixer::can_start(const TickableContext& context) const
{
	const auto& ctx = cast(context);
	return ctx.color_left_ != Color::uncolored && ctx.color_right_ != Color::uncolored;
}

bool Mixer::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		send_dye(ctx.left_pos_, context.direction, ctx.color_left_, map))
	{
		ctx.color_left_ = Color::uncolored;
		ctx.color_right_ = Color::uncolored;
		return true;
	}
	return false;
}
