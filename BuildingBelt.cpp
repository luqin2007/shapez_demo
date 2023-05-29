#include "BuildingBelt.h"

static string tex_forward[14]
{
	"forward_0.png", "forward_1.png", "forward_2.png", "forward_3.png", "forward_4.png",
	"forward_5.png", "forward_6.png", "forward_7.png", "forward_8.png", "forward_9.png",
	"forward_10.png", "forward_11.png", "forward_12.png", "forward_13.png",
};

static string tex_left[14]
{
	"left_0.png", "left_1.png", "left_2.png", "left_3.png", "left_4.png",
	"left_5.png", "left_6.png", "left_7.png", "left_8.png", "left_9.png",
	"left_10.png", "left_11.png", "left_12.png", "left_13.png",
};

static string tex_right[14]
{
	"right_0.png", "right_1.png", "right_2.png", "right_3.png", "right_4.png",
	"right_5.png", "right_6.png", "right_7.png", "right_8.png", "right_9.png",
	"right_10.png", "right_11.png", "right_12.png", "right_13.png",
};

BuildingContext* BuildingBelt::build_context(const Vec2I& pos, Side direction) const
{
	return new BeltContext(*this, pos, direction, direction);
}

bool BuildingBelt::can_receive(const Vec2I& pos, const Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingBelt::can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const
{
	const BeltContext& ctx = cast(context);
	return can_receive(pos, side, context) && ctx.p_item_ != 3 && ctx.item_pos[ctx.p_item_] > ctx.max_pos_[1];
}

bool BuildingBelt::can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, const Side side,
                                     const BuildingContext& context) const
{
	const BeltContext& ctx = cast(context);
	return can_receive(pos, side, context) && ctx.p_item_ != 3 && ctx.item_pos[ctx.p_item_] > ctx.max_pos_[1];
}

void BuildingBelt::receive_dye(const Color color, const Vec2I& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.types[ctx.p_item_] = ItemType::dye;
	ctx.indices[ctx.p_item_] = ctx.p_dye;
	ctx.item_pos[ctx.p_item_] = 0;
	ctx.dyes[ctx.p_dye] = color;
	ctx.p_dye = (ctx.p_dye + 1) % 4;
	ctx.p_item_--;
}

void BuildingBelt::receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
                                 BuildingContext& context) const
{
	auto& ctx = cast(context);
	ctx.types[ctx.p_item_] = ItemType::shape;
	ctx.indices[ctx.p_item_] = ctx.p_shape;
	ctx.item_pos[ctx.p_item_] = 0;
	ctx.shapes[ctx.p_shape] = shape;
	ctx.p_shape = (ctx.p_shape + 1) % 4;
	ctx.p_item_--;
}

void BuildingBelt::update(BuildingContext& context, GameMap& map) const
{
	auto& ctx = cast(context);

	const float ss = ctx.speed_ * current_game->timer().delta;
	for (int i = 1; i <= ctx.p_item_; ++i)
	{
		ctx.item_pos[i] += ss;
		if (ctx.item_pos[i] > ctx.max_pos_[i])
		{
			ctx.item_pos[i] = ctx.max_pos_[i];
		}
	}

	// 可输出
	bool send = false;
	if (ctx.types[3] == ItemType::dye)
	{
		send = send_dye(context.pos, ctx.output_, ctx.dyes[ctx.indices[3]], map);
	}
	else if (ctx.types[3] == ItemType::shape)
	{
		send = send_shape(context.pos, ctx.output_, ctx.shapes[ctx.indices[3]], map);
	}
	if (send)
	{
		// 迁移
		ctx.types[3] = ctx.types[2];
		ctx.types[2] = ctx.types[1];
		ctx.types[1] = ctx.types[0];

		ctx.indices[3] = ctx.indices[2];
		ctx.indices[2] = ctx.indices[1];
		ctx.indices[1] = ctx.indices[0];

		ctx.item_pos[3] = ctx.item_pos[2];
		ctx.item_pos[2] = ctx.item_pos[1];
		ctx.item_pos[1] = ctx.item_pos[0];

		ctx.p_item_++;
	}
}

const string& BuildingBelt::get_building_texture(const BuildingContext& context) const
{
	return tex_forward[((current_game->timer().running_ms - cast(context).place_time_) / 10) % 14];
}

void BuildingBelt::free_context(BuildingContext* context) const
{
	delete static_cast<BeltContext*>(context);
}

BuildingContext* BuildingBeltL::build_context(const Vec2I& pos, const Side direction) const
{
	return new BeltContext(*this, pos, direction, --direction);
}

const string& BuildingBeltL::get_building_texture(const BuildingContext& context) const
{
	return tex_left[((current_game->timer().running_ms - cast(context).place_time_) / 10) % 14];
}

BuildingContext* BuildingBeltR::build_context(const Vec2I& pos, const Side direction) const
{
	return new BeltContext(*this, pos, direction, ++direction);
}

const string& BuildingBeltR::get_building_texture(const BuildingContext& context) const
{
	return tex_right[((current_game->timer().running_ms - cast(context).place_time_) / 10) % 14];
}
