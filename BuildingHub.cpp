#include "BuildingHub.h"

bool BuildingHub::can_receive(const ivec2& pos, Side side, const BuildingContext& context) const
{
	return true;
}

bool BuildingHub::can_receive_item(const Item& item, const ivec2& pos, Side side, const BuildingContext& context) const
{
	return true;
}

void BuildingHub::receive(Item item, const ivec2& pos, Side side, BuildingContext& context) const
{
	auto& ctx = cast(context);
	if (item == ctx.item)
	{
		ctx.accept_count++;
		if (ctx.accept_count == ctx.total_count)
		{
			set_next_level(ctx);
		}
	}
}

void BuildingHub::update(BuildingContext& context, const GameMap& map) const
{
}

void BuildingHub::set_next_level(HubContext& context)
{
	context.accept_count = 0;
	context.total_count = context.level * 10 + 5;
	context.level++;
	context.item = static_cast<Item>(ShapeItem{ColoredPart{Part::RECT, Color::cyan}});
}
