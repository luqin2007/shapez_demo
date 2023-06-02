#pragma once

#include "Building.h"
#include "BuildingContext.h"

constexpr time_t FAST = 500;
constexpr time_t MIDDLE = 1500;
constexpr time_t SLOW = 3000;

enum class BuildingStatus
{
	/**
	 * \brief 状态：空闲（无输入或输入不足）
	 */
	waiting,

	/**
	 * \brief 状态：运行中
	 */
	running,

	/**
	 * \brief 状态：阻塞（产物无法完全输出）
	 */
	blocking
};

class TickableBuilding;

class MinerRenderer;

class TickableContext : public BuildingContext
{
	friend TickableBuilding;
	friend BuildingRenderer;
public:
	TickableContext(const Building& building, const Vec2I& pos, const Side direction, const time_t required_time)
		: BuildingContext(building, pos, direction), required_time_(required_time)
	{
	}
	
protected:
	/**
	 * \brief 当前工作状态
	 */
	BuildingStatus status_ = BuildingStatus::waiting;

	/**
	 * \brief 当前执行时间
	 */
	time_t current_time_ = 0;

	/**
	 * \brief 需要的总时间
	 */
	const time_t required_time_;
};


/**
 * \brief 需要时间处理的建筑类型
 */
class TickableBuilding : public Building
{
public:
	void update(BuildingContext& context, GameMap& map) const override;

	static TickableContext& cast(BuildingContext& context)
	{
		return static_cast<TickableContext&>(context);
	}

	static const TickableContext& cast(const BuildingContext& context)
	{
		return static_cast<const TickableContext&>(context);
	}
protected:
	TickableBuilding() = default;

	/**
	 * \brief 检查是否可以运行
	 */
	virtual bool can_start(const TickableContext& context) const = 0;

	/**
	 * \brief 每次当处于阻塞状态时的行为
	 * \return 若返回 true，则表示阻塞状态结束
	 */
	virtual bool on_blocking(TickableContext& context, const GameMap& map) const = 0;
};
