#include "Hub.h"

#include "HubRenderer.h"

BuildingContext* Hub::build_context(const Vec2I& pos, const Side direction) const
{
	return new HubContext(*this, pos, direction);
}

bool Hub::can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool Hub::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool Hub::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                            const BuildingContext& context) const
{
	return true;
}

void Hub::receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
}

void Hub::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	if (ctx.shapes == shape)
	{
		ctx.accept_count++;
	}
}

void Hub::update(BuildingContext& context, GameMap& map) const
{
	auto& ctx = cast(context);
	if (ctx.level == 0)
	{
		set_next_level(cast(context));;
	}
	if (ctx.accept_count >= ctx.total_count)
	{
		set_next_level(ctx);
	}
}

void Hub::free_context(BuildingContext* context) const
{
	delete static_cast<HubContext*>(context);
}

const BuildingRenderer& Hub::get_renderer() const
{
	static HubRenderer renderer;
	return renderer;
}

vector<Vec2I> Hub::all_positions(const Vec2I& pos, Side direction) const
{
	vector<Vec2I> p;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			p.emplace_back(pos.x + i, pos.y + j);
		}
	}
	return p;
}

void Hub::set_next_level(HubContext& context)
{
	context.accept_count = 0;
	context.total_count = context.level * 10 + 5;
	context.level++;

	if (context.level <= 10)
	{
		const Color color = random_color(context.level);
		const Shape shape = random_shape();
		context.shapes.up_left.first = color;
		context.shapes.up_left.second = shape;
		context.shapes.up_right.first = color;
		context.shapes.up_right.second = shape;
		context.shapes.down_left.first = color;
		context.shapes.down_left.second = shape;
		context.shapes.down_right.first = color;
		context.shapes.down_right.second = shape;
	}
	else if (context.level <= 15)
	{
		const Color color1 = random_color(context.level);
		const Color color2 = random_color(context.level);
		const Shape shape1 = random_shape();
		const Shape shape2 = random_shape();
		if (random_int() % 2)
		{
			context.shapes.up_left.first = color1;
			context.shapes.up_left.second = shape1;
			context.shapes.up_right.first = color1;
			context.shapes.up_right.second = shape1;
			context.shapes.down_left.first = color2;
			context.shapes.down_left.second = shape2;
			context.shapes.down_right.first = color2;
			context.shapes.down_right.second = shape2;
		}
		else
		{
			context.shapes.up_left.first = color1;
			context.shapes.up_left.second = shape1;
			context.shapes.up_right.first = color2;
			context.shapes.up_right.second = shape2;
			context.shapes.down_left.first = color1;
			context.shapes.down_left.second = shape1;
			context.shapes.down_right.first = color2;
			context.shapes.down_right.second = shape2;
		}
	}
	else
	{
		const Color color1 = random_color(context.level);
		const Color color2 = random_color(context.level);
		const Color color3 = random_color(context.level);
		const Color color4 = random_color(context.level);
		const Shape shape1 = random_shape();
		const Shape shape2 = random_shape();
		const Shape shape3 = random_shape();
		const Shape shape4 = random_shape();
		context.shapes.up_left.first = color1;
		context.shapes.up_left.second = shape1;
		context.shapes.up_right.first = color2;
		context.shapes.up_right.second = shape2;
		context.shapes.down_left.first = color3;
		context.shapes.down_left.second = shape3;
		context.shapes.down_right.first = color4;
		context.shapes.down_right.second = shape4;
	}
}

Color Hub::random_color(const int level)
{
	if (level >= 10)
	{
		switch (random_int() % 4)
		{
		case 0:
			// 25%
			return Color::yellow;
		case 1:
			// 25%
			return Color::cyan;
		case 2:
			// 25%
			return Color::purple;
		default:
			switch (random_int() % 4)
			{
			case 0:
				// 6.25%
				return Color::red;
			case 1:
				// 6.25%
				return Color::blue;
			case 2:
				// 6.25%
				return Color::green;
			default:
				// 6.25%
				return Color::white;
			}
		}
	}
	else if (level >= 5)
	{
		switch (random_int() % 4)
		{
		case 0:
			// 25%
			return Color::red;
		case 1:
			// 25%
			return Color::blue;
		case 2:
			// 25%
			return Color::green;
		default:
			// 25%
			return Color::uncolored;
		}
	}

	return Color::uncolored;
}

Shape Hub::random_shape()
{
	switch (random_int() % 3)
	{
	case 0:
	default:
		return Shape::rect;
	case 1:
		return Shape::fan;
	case 2:
		return Shape::star;
	}
}
