#include "TickableBuilding.h"

#include "GameLogic.h"

void TickableBuilding::update(BuildingContext& context, GameMap& map) const
{
	switch (auto& ctx = cast(context); ctx.status_)
	{
	case BuildingStatus::waiting:

		if (can_start(ctx))
		{
			// 开始运行
			ctx.current_time_ = 0;
			ctx.status_ = BuildingStatus::running;
		}
		break;

	case BuildingStatus::running:

		ctx.current_time_ += current_game->timer().delta_ms;
		if (ctx.current_time_ >= ctx.required_time_)
		{
			// 任务结束
			if (on_blocking(ctx, map))
			{
				// 进入空闲状态
				ctx.status_ = BuildingStatus::waiting;
			}
			else
			{
				// 进入阻塞状态
				ctx.status_ = BuildingStatus::blocking;
			}
		}
		break;

	case BuildingStatus::blocking:

		if (on_blocking(ctx, map))
		{
			// 进入空闲状态
			ctx.status_ = BuildingStatus::waiting;
		}
		break;
	}
}
