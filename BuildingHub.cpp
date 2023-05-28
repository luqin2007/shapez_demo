#include "BuildingHub.h"

BuildingContext BuildingHub::build_context(const Vec2I& pos, const Side direction) const
{
	return static_cast<BuildingContext>(HubContext(*this, pos, direction));
}

bool BuildingHub::can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool BuildingHub::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool BuildingHub::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                    const BuildingContext& context) const
{
	return true;
}

void BuildingHub::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void BuildingHub::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	if (ctx.shapes == shape)
	{
		ctx.accept_count++;
	}
	if (ctx.accept_count == ctx.total_count)
	{
		set_next_level(ctx);
	}
}

void BuildingHub::update(BuildingContext& context, GameMap& map) const
{
}

void BuildingHub::set_next_level(HubContext& context)
{
	context.accept_count = 0;
	context.total_count = context.level * 10 + 5;
	context.level++;

	Shape shape;
	auto color = Color::uncolored;

	// 随机形状
	// 1/3 概率任意形状
	switch (random_int() % 3)
	{
	case 0:
	default:
		shape = Shape::rect;
		break;
	case 1:
		shape = Shape::fan;
		break;
	case 2:
		shape = Shape::star;
		break;
	}
	// 随机颜色
	// >= 10 级：75% 两种混合色；18.75% 单色；6.25% 白色
	// >= 5 级：75% 单色；25% 无色
	// < 5 级：无色
	if (context.level >= 10)
	{
		switch (random_int() % 4)
		{
		case 0:
			// 25%
			color = Color::yellow;
			break;
		case 1:
			// 25%
			color = Color::cyan;
			break;
		case 2:
			// 25%
			color = Color::purple;
			break;
		default:
			switch (random_int() % 4)
			{
			case 0:
				// 6.25%
				color = Color::red;
				break;
			case 1:
				// 6.25%
				color = Color::blue;
				break;
			case 2:
				// 6.25%
				color = Color::green;
				break;
			default:
				// 6.25%
				color = Color::white;
			}
		}
	}
	else if (context.level >= 5)
	{
		switch (random_int() % 4)
		{
		case 0:
			// 25%
			color = Color::red;
			break;
		case 1:
			// 25%
			color = Color::blue;
			break;
		case 2:
			// 25%
			color = Color::green;
			break;
		default:
			// 25%
			color = Color::uncolored;
		}
	}

	context.shapes = {
		{color, shape},
		{color, shape},
		{color, shape},
		{color, shape}
	};
}
