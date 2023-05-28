#include "BuildingBalancer.h"

#include "ItemType.h"

BuildingContext BuildingBalancer::build_context(const Vec2I& pos, const Side direction) const
{
	return static_cast<BuildingContext>(BalancerContext(*this, pos, direction));
}

bool BuildingBalancer::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingBalancer::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return can_receive(side, context);
}

bool BuildingBalancer::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                         const BuildingContext& context) const
{
	return can_receive(side, context);
}

void BuildingBalancer::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.colors_.push(color);
	ctx.types_.push(ItemType::dye);
}

void BuildingBalancer::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                     BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.shapes_.push(shape);
	ctx.types_.push(ItemType::shape);
}

bool BuildingBalancer::can_start(TickableContext& context, const GameMap& map) const
{
	return !cast(context).types_.empty();
}

bool BuildingBalancer::on_blocking(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);
	send_first_item(ctx, map);
	return ctx.types_.size() < ctx.max_items_;
}

bool BuildingBalancer::on_finished(TickableContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);
	send_first_item(ctx, map);
	return ctx.types_.size() < ctx.max_items_;
}

bool BuildingBalancer::can_receive(const Side side, const BuildingContext& context) const
{
	// 方向正确
	if (side != -context.direction)
	{
		return false;
	}
	// 位置空闲
	if (const auto& ctx = cast(context);
		ctx.types_.size() == ctx.max_items_)
		return false;

	return true;
}

void BuildingBalancer::send_first_item(BalancerContext& context, const GameMap& map)
{
	const auto& type = context.types_.front();
	if (context.side_ == 0)
	{
		if (type == ItemType::dye)
		{
			if (send_dye(context.pos, context.direction, context.colors_.front(), map))
			{
				context.types_.pop();
				context.colors_.pop();
				// 交替输出
				context.side_ = !context.side_;
			}
			else if (send_dye(context.pos + (--context.direction), context.direction, context.colors_.front(), map))
			{
				context.types_.pop();
				context.colors_.pop();
			}
		}
		else
		{
			if (send_shape(context.pos, context.direction, context.shapes_.front(), map))
			{
				context.types_.pop();
				context.shapes_.pop();
				// 交替输出
				context.side_ = !context.side_;
			}
			else if (send_shape(context.pos + (--context.direction), context.direction, context.shapes_.front(), map))
			{
				context.types_.pop();
				context.shapes_.pop();
			}
		}
	}
	else
	{
		if (type == ItemType::dye)
		{
			if (send_dye(context.pos + (--context.direction), context.direction, context.colors_.front(), map))
			{
				context.types_.pop();
				context.colors_.pop();
				// 交替输出
				context.side_ = !context.side_;
			}
			else if (send_dye(context.pos, context.direction, context.colors_.front(), map))
			{
				context.types_.pop();
				context.colors_.pop();
			}
		}
		else
		{
			if (send_shape(context.pos + (--context.direction), context.direction, context.shapes_.front(), map))
			{
				context.types_.pop();
				context.shapes_.pop();
				// 交替输出
				context.side_ = !context.side_;
			}
			else if (send_shape(context.pos, context.direction, context.shapes_.front(), map))
			{
				context.types_.pop();
				context.shapes_.pop();
			}
		}
	}
}
