#include "BuildingBelt.h"

bool BuildingBelt::can_receive(const ivec2& pos, Side side, const BuildingContext& context) const
{
	return side == -context.direction;
}

bool BuildingBelt::can_receive_item(const Item& item, const ivec2& pos, Side side, const BuildingContext& context) const
{
	BeltContext ctx = cast(context);
	if (!can_receive(pos, side, context))
	{
		return false;
	}

	return ctx.items.size() < ctx.max_item_count_ && (ctx.items.empty() || ctx.items.front().second >= ctx.speed_);
}

void BuildingBelt::receive(Item item, const ivec2& pos, Side side, BuildingContext& context) const
{
	cast(context).items.push_front({item, 0.0f});
}

void BuildingBelt::update(BuildingContext& context, const GameMap& map) const
{
	auto& ctx = cast(context);

	for (auto &item: ctx.items)
	{
		item.second += ctx.speed_;
	}

	while (ctx.items.back().second >= 1.0f)
	{
		if (send_item(ctx.pos, ctx.output_, ctx.items.back().first, map))
		{
			ctx.items.pop_back();
		}
		else
		{
			break;
		}
	}
}
