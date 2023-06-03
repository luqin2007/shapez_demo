#include "UndergroundBelt2.h"

#include <GLFW/glfw3.h>

#include "GameLogic.h"
#include "GameWindow.h"
#include "ItemType.h"
#include "UndergroundBelt1.h"
#include "UndergroundBelt2Renderer.h"

BuildingContext* UndergroundBelt2::build_context(const Vec2I& pos, const Side direction) const
{
	return new UndergroundBelt2Context{*this, pos, direction};
}

bool UndergroundBelt2::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == opposite(context.direction);
}

bool UndergroundBelt2::can_receive_dye(Color color, const Vec2I& pos, const Side side,
                                       const BuildingContext& context) const
{
	return can_receive(pos, side, context) && cast(context).type_ == ItemType::none;
}

bool UndergroundBelt2::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                         const BuildingContext& context) const
{
	return can_receive(pos, side, context) && cast(context).type_ == ItemType::none;
}

void UndergroundBelt2::receive_dye(const Color color, const Vec2I& pos, Side side,
                                   BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.color_ = color;
	ctx.type_ = ItemType::dye;
}

void UndergroundBelt2::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                     BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.shapes_ = shape;
	ctx.type_ = ItemType::shape;
}

void UndergroundBelt2::free_context(BuildingContext* context) const
{
	delete static_cast<UndergroundBelt2Context*>(context);
}

const BuildingRenderer& UndergroundBelt2::get_renderer() const
{
	static UndergroundBelt2Renderer renderer;
	return renderer;
}

vector<Vec2I> UndergroundBelt2::all_positions(const Vec2I& pos, Side direction) const
{
	vector<Vec2I> p;
	p.push_back(pos);
	return p;
}

void UndergroundBelt2::on_placed(BuildingContext& context) const
{
	if (current_game)
	{
		BuildingContext* ctx = current_game->map().get_building(current_game->current_building_data);
		UndergroundBelt1::cast(*ctx).target_ = context.pos;

		current_game->current_building = nullptr;
		glfwSetInputMode(current_window->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

bool UndergroundBelt2::can_place(const Vec2I& pos, const Side direction, const GameMap& map) const
{
	if (!TickableBuilding::can_place(pos, direction, map))
	{
		return false;
	}
	if (current_game)
	{
		const auto& p1 = current_game->current_building_data;
		// 类型正确，方向相同
		if (const BuildingContext* pc1 = map.get_building(p1);
			pc1 && pc1->building == UndergroundBelt1::instance() && direction == pc1->direction)
		{
			// 位置正确
			if (direction == Side::up || direction == Side::down)
			{
				return pos.y == pc1->pos.y && abs(pos.x - pc1->pos.x) <= 5;
			}
			else
			{
				return pos.x == pc1->pos.x && abs(pos.y - pc1->pos.y) <= 5;
			}
		}
	}
	return false;
}

bool UndergroundBelt2::can_start(const TickableContext& context) const
{
	return cast(context).type_ != ItemType::none;
}

bool UndergroundBelt2::on_blocking(TickableContext& context, const GameMap& map) const
{
	if (auto& ctx = cast(context);
		ctx.type_ == ItemType::dye)
	{
		if (send_dye(context.pos, context.direction, cast(context).color_, map))
		{
			ctx.type_ = ItemType::none;
			return true;
		}
		return false;
	}
	else if (ctx.type_ == ItemType::shape)
	{
		if (send_shape(context.pos, context.direction, cast(context).shapes_, map))
		{
			ctx.type_ = ItemType::none;
			return true;
		}
		return false;
	}

	return true;
}
