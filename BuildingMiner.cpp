#include "BuildingMiner.h"

#include "GameLogic.h"

bool BuildingMiner::can_receive(const ivec2& pos, Side side, const BuildingContext& context) const
{
	return false;
}

bool BuildingMiner::can_receive_item(const Item& item, const ivec2& pos, Side side,
                                     const BuildingContext& context) const
{
	return false;
}

void BuildingMiner::receive(Item item, const ivec2& pos, Side side, BuildingContext& context) const
{
}

void BuildingMiner::update(BuildingContext& context, const GameMap& map) const
{
	const ResourceType& res = map.get_resource(context.pos);
	if (res == ResourceType::EMPTY)
	{
		return;
	}

	const Item item = res.create_item();
	MinerContext& ctx = cast(context);
	ctx.waiting_time_ += current_game->timer().delta_ms;
	if (ctx.waiting_time_ >= ctx.max_waiting_time_)
	{
		if (send_item(context.pos, context.direction, item, map))
		{
			ctx.waiting_time_ = 0;
		}
	}
}
