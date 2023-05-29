#pragma once

#include <vector>
#include <memory>

#include "vec.h"

#include "GameMap.h"
#include "BuildingSize.h"
#include "BuildingContext.h"
#include "ColoredShapes.h"

using std::vector;
using std::unique_ptr;
using std::string;

enum class ItemType;
enum class Color;

/**
 * \brief 建筑类型，只保存建筑的行为，不保存建筑数据
 */
class Building
{
public:
	/**
	 * \brief 建筑大小 
	 */
	const BuildingSize size;

	/**
	 * \brief 图标纹理名称
	 */
	const string tex_icon;

	/**
	 * \brief 持有时纹理名称
	 */
	const string tex_hover;

	/**
	 * \brief 放下后纹理名称
	 */
	const string tex_building;

	/**
	 * \brief 下一个变种的引用
	 */
	const Building* next_variant = this;

	/**
	 * \brief 根据建筑生成数据
	 * \param pos 建筑位置
	 * \param direction 方向
	 * \return 数据
	 */
	[[nodiscard]]
	virtual BuildingContext* build_context(const Vec2I& pos, Side direction) const = 0;

	/**
	 * \brief 用于释放建筑数据
	 * \param context 建筑数据
	 */
	virtual void free_context(BuildingContext* context) const = 0;

	/**
	 * \brief 判断对应位置是否可能接收物品输入，用于传送带等可连接建筑检查
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	[[nodiscard]]
	virtual bool can_receive(const Vec2I& pos, Side side, const BuildingContext& context) const = 0;

	/**
	 * \brief 判断对应位置是否可以输入某染料，用于实际物品输入校验
	 * \param color 输入的染料
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	[[nodiscard]]
	virtual bool can_receive_dye(Color color, const Vec2I& pos, Side side, const BuildingContext& context) const = 0;

	/**
	 * \brief 判断对应位置是否可以输入某图形，用于实际物品输入校验
	 * \param shape 输入的物品
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	[[nodiscard]]
	virtual bool can_receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                               const BuildingContext& context) const = 0;

	/**
	 * \brief 当建筑放下时调用
	 * \param context 放下的建筑
	 */
	virtual void on_placed(BuildingContext& context) const
	{
	}

	/**
	 * \brief 从某位置接收染料，调用该方法之前应当保证通过 can_receive_dye 检验
	 * \param color 输入物品
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	virtual void receive_dye(Color color, const Vec2I& pos, Side side, BuildingContext& context) const = 0;

	/**
	 * \brief 从某位置接收图形物品，调用该方法之前应当保证通过 can_receive_shape 检验
	 * \param shape 输入物品
	 * \param pos 目标单元
	 * \param side 输入方向
	 * \param context 建筑数据
	 */
	virtual void receive_shape(const ColoredShapes& shape, const Vec2I& pos, Side side,
	                           BuildingContext& context) const = 0;

	/**
	 * \brief 获取当前显示的纹理贴图
	 * \param context 建筑数据
	 * \return 贴图纹理
	 */
	[[nodiscard]] virtual const string& get_building_texture(const BuildingContext& context) const
	{
		return tex_building;
	}

	/**
	 *\brief 更新建筑状态
	 */
	virtual void update(BuildingContext& context, GameMap& map) const = 0;

	/**
	 * \brief 测试是否能正常放下
	 * \param pos 建筑所在位置
	 * \param size 建筑大小
	 * \param direction 建筑方向
	 * \param map 游戏地图
	 */
	[[nodiscard]]
	static bool can_place(const Vec2I& pos, BuildingSize size, Side direction, const GameMap& map);

	/**
	 * \brief 将建筑大小枚举转换为 Vec2I 表示的大小
	 * \param size 建筑大小
	 * \return 以 Vec2I 形式表示的建筑大小
	 */
	static Vec2I size_as_vec(BuildingSize size);

	/**
	 * \brief 获取建筑占用的所有方块
	 * \param pos 建筑所在位置
	 * \param size 建筑大小
	 * \param direction 建筑方向
	 * \return 所有方向
	 */
	static vector<Vec2I> all_positions(const Vec2I& pos, BuildingSize size, Side direction);

	/**
	 * \brief 尝试向某个方向发送染料
	 * \param pos 发出点
	 * \param direction 发送方向
	 * \param color 发送染料
	 * \param map 地图
	 * \return 是否成功发送
	 */
	static bool send_dye(const Vec2I& pos, Side direction, Color color, const GameMap& map);

	/**
	 * \brief 尝试向某个方向发送物品
	 * \param pos 发出点
	 * \param direction 发送方向
	 * \param shape 发送形状
	 * \param map 地图
	 * \return 是否成功发送
	 */
	static bool send_shape(const Vec2I& pos, Side direction, const ColoredShapes& shape, const GameMap& map);

	Building(const Building&) = delete;

	Building(Building&&) = delete;

	virtual ~Building() = default;

	Building& operator=(const Building&) = delete;

	Building& operator=(const Building&&) = delete;

protected:
	/**
	 * \brief 不公开的构造函数，仅由对应类型创建
	 * \param size 建筑大小
	 * \param tex_icon 图标纹理名称
	 * \param tex_hover 持有时纹理名称
	 * \param tex_building 放下后纹理名称
	 */
	Building(const BuildingSize size, string tex_icon, string tex_building, string tex_hover)
		: size(size), tex_icon(std::move(tex_icon)), tex_hover(std::move(tex_hover)),
		  tex_building(std::move(tex_building))
	{
	}
};
