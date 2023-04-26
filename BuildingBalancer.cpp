#include "BuildingBalancer.h"

bool BuildingBalancer::can_place(const ivec2& pos, Side direction, ivec2* prev, const GameMap& map) const
{
	if (map.get_building(pos) && typeid(BuildingBelt) != typeid(map.get_building(pos)->building)) return false;
	auto ap = pos + ++direction;
	if (map.get_building(ap) && typeid(BuildingBelt) != typeid(map.get_building(ap)->building)) return false;
	return true;
}

PlaceState BuildingBalancer::place_at(BuildingContext& context, GameMap& map) const
{
	context.all.push_back(context.pos + ++context.direction);
	return PlaceState::PLACED;
}

bool BuildingBalancer::can_receive(Item& item, ivec2& pos, Side side, BalancerContext& context) const
{
	return context.queue.size() != context.maxItemCached && side == -context.direction;
}

void BuildingBalancer::receive(Item& item, ivec2& pos, Side side, BalancerContext& context) const
{
	context.queue.push_back({item, 0});
}

void BuildingBalancer::update(BalancerContext& context, const GameMap& map) const
{
	context.outputWaiting += context.timeDelta;
	float pp = context.itemDelay / context.maxItemCached;
	float pt = context.itemDelay;
	for (auto& item : context.queue)
	{
		item.second += context.timeDelta;
		if (item.second > pt) item.second = pt;
		pt = item.second - pp;
	}
	if (context.queue.end()->second >= context.itemDelay && context.outputWaiting >= context.outputDelay)
	{
		Item& item = context.queue.front().first;
		if (context.outputIndex)
		{
			// 第一次尝试
			ivec2 out = context.pos + context.direction + ++context.direction;
			if (map.get_building(out))
			{
				BuildingContext& rec = *map.get_building(out);
				if (rec.building.can_receive(item, out, -context.direction, context))
				{
					rec.building.receive(item, out, -context.direction, context);
					context.queue.pop_front();
					context.outputIndex = 0;
					context.outputWaiting = 0;
					return;
				}
			}
			out = out + --context.direction;
			// 第二次尝试
			if (map.get_building(out))
			{
				BuildingContext& rec = *map.get_building(out);
				if (rec.building.can_receive(item, out, -context.direction, context))
				{
					rec.building.receive(item, out, -context.direction, context);
					context.queue.pop_front();
					context.outputIndex = 1;
					context.outputWaiting = 0;
					return;
				}
			}
		}
		else
		{
			// 第一次尝试
			ivec2 out = context.pos + context.direction + ++context.direction;
			if (map.get_building(out))
			{
				BuildingContext& rec = *map.get_building(out);
				if (rec.building.can_receive(item, out, -context.direction, context))
				{
					rec.building.receive(item, out, -context.direction, context);
					context.queue.pop_front();
					context.outputIndex = 1;
					context.outputWaiting = 0;
					return;
				}
			}
			out = out + --context.direction;
			// 第二次尝试
			if (map.get_building(out))
			{
				BuildingContext& rec = *map.get_building(out);
				if (rec.building.can_receive(item, out, -context.direction, context))
				{
					rec.building.receive(item, out, -context.direction, context);
					context.queue.pop_front();
					context.outputIndex = 0;
					context.outputWaiting = 0;
					return;
				}
			}
		}
	}
}
