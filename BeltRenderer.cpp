#include "BeltRenderer.h"

#include "Belt.h"
#include "GameLogic.h"
#include "GameRenderer.h"

void BeltRenderer::draw_building(const int row, const int col,
                                 const BuildingContext& context, GameRenderer& renderer, const GameMap& map) const
{
	const BeltContext& ctx = Belt::cast(context);
	const int index = (current_game->timer().running_ms / delta_time_) % 14;
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas,
	                         get_building_tex(index), context.direction);
}

void BeltRenderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
                                const GameMap& map) const
{
	renderer.tex_drawer.push(x - EXT_SIZE, y - EXT_SIZE, x + map.cell_size + EXT_SIZE, y + map.cell_size + EXT_SIZE,
	                         renderer.atlas, holding_, direction);
}

void BeltRenderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
	                         x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
	                         renderer.atlas, "belt_icon.png", Side::up);
}

void BeltDirectRenderer::draw_items_in_building(const int row, const int col, const BuildingContext& context,
                                                GameRenderer& renderer, const GameMap& map) const
{
	const BeltContext& ctx = Belt::cast(context);
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;

	if (ctx.item_count_)
	{
		// 绘制第一个物品
		const float item_pos = min(ctx.item_pos_[ctx.first_], 1.0f);
		const auto p0 = offset_direct(context.direction, map.cell_size, item_pos, x0, y0);
		if (ctx.item_types_[ctx.first_] == ItemType::dye)
		{
			draw_color(p0.x, p0.y, map.cell_size, renderer, ctx.dyes_[ctx.first_]);
		}
		else
		{
			draw_item(p0.x, p0.y, map.cell_size, renderer, ctx.shapes_[ctx.first_]);
		}
	}
	if (ctx.item_count_ == 2)
	{
		// 绘制第二个物品
		const float item_pos = min(ctx.item_pos_[ctx.second_], 0.5f);
		const auto p0 = offset_direct(context.direction, map.cell_size, item_pos, x0, y0);
		if (ctx.item_types_[ctx.second_] == ItemType::dye)
		{
			draw_color(p0.x, p0.y, map.cell_size, renderer, ctx.dyes_[ctx.second_]);
		}
		else
		{
			draw_item(p0.x, p0.y, map.cell_size, renderer, ctx.shapes_[ctx.second_]);
		}
	}
}

const string& BeltDirectRenderer::get_building_tex(const int index) const
{
	return tex_forward_[index];
}

Vec2 BeltDirectRenderer::offset_direct(const Side direction, const float cell_size, const float p,
                                       const float x0, const float y0)
{
	switch (direction)
	{
	case Side::up:
		return {x0 + 0.3f * cell_size, y0 - (p - 0.7f) * cell_size};
	case Side::down:
		return {x0 + 0.3f * cell_size, y0 + (p - 0.1f) * cell_size};
	case Side::left:
		return {x0 - (p - 0.7f) * cell_size, y0 + 0.3f * cell_size};
	case Side::right:
		return {x0 + (p - 0.1f) * cell_size, y0 + 0.3f * cell_size};
	}
	return {};
}

void BeltLeftRenderer::draw_items_in_building(const int row, const int col, const BuildingContext& context,
                                              GameRenderer& renderer, const GameMap& map) const
{
	const BeltContext& ctx = Belt::cast(context);
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;

	if (ctx.item_count_)
	{
		// 绘制第一个物品
		const float item_pos = min(ctx.item_pos_[ctx.first_], 1.0f);
		const auto p0 = offset_left(context.direction, map.cell_size, item_pos, x0, y0);
		if (ctx.item_types_[ctx.first_] == ItemType::dye)
		{
			draw_color(p0.x, p0.y, map.cell_size, renderer, ctx.dyes_[ctx.first_]);
		}
		else
		{
			draw_item(p0.x, p0.y, map.cell_size, renderer, ctx.shapes_[ctx.first_]);
		}
	}
	if (ctx.item_count_ == 2)
	{
		// 绘制第二个物品
		const float item_pos = min(ctx.item_pos_[ctx.second_], 0.5f);
		const auto p0 = offset_left(context.direction, map.cell_size, item_pos, x0, y0);
		if (ctx.item_types_[ctx.second_] == ItemType::dye)
		{
			draw_color(p0.x, p0.y, map.cell_size, renderer, ctx.dyes_[ctx.second_]);
		}
		else
		{
			draw_item(p0.x, p0.y, map.cell_size, renderer, ctx.shapes_[ctx.second_]);
		}
	}
}

const string& BeltLeftRenderer::get_building_tex(const int index) const
{
	return tex_left_[index];
}

Vec2 BeltLeftRenderer::offset_left(const Side direction, const float cell_size, const float p,
                                   const float x0, const float y0)
{
	if (p <= 0.3f)
	{
		// 上升 0.3 -> 0.2
		const float pp = p / 3 * 2;
		switch (direction)
		{
		case Side::up:
			return {x0 + 0.3f * cell_size, y0 + (0.7f - pp) * cell_size};
		case Side::down:
			return {x0 + 0.3f * cell_size, y0 + (-0.1f + pp) * cell_size};
		case Side::left:
			return {x0 + (0.7f - pp) * cell_size, y0 + 0.3f * cell_size};
		case Side::right:
			return {x0 + (-0.1f + pp) * cell_size, y0 + 0.3f * cell_size};
		}
	}
	else if (p <= 0.7f)
	{
		// 斜向 0.4 -> 0.2
		const float pp = (p - 0.3f) / 2;
		switch (direction)
		{
		case Side::up:
			return {x0 + (0.3f - pp) * cell_size, y0 + (0.5f - pp) * cell_size};
		case Side::down:
			return {x0 + (0.3f + pp) * cell_size, y0 + (0.1f + pp) * cell_size};
		case Side::left:
			return {x0 + (0.5f - pp) * cell_size, y0 + (0.3f + pp) * cell_size};
		case Side::right:
			return {x0 + (0.1f + pp) * cell_size, y0 + (0.3f - pp) * cell_size};
		}
	}
	else
	{
		// 横向 0.3 -> 0.4
		const float pp = (p - 0.7f) / 3 * 4;
		switch (direction)
		{
		case Side::up:
			return {x0 + (0.1f - pp) * cell_size, y0 + 0.3f * cell_size};
		case Side::down:
			return {x0 + (0.5f + pp) * cell_size, y0 + 0.3f * cell_size};
		case Side::left:
			return {x0 + 0.3f * cell_size, y0 + (0.5f + pp) * cell_size};
		case Side::right:
			return {x0 + 0.3f * cell_size, y0 + (0.1f - pp) * cell_size};
		}
	}
	return {};
}

void BeltRightRenderer::draw_items_in_building(const int row, const int col, const BuildingContext& context,
                                               GameRenderer& renderer, const GameMap& map) const
{
	const BeltContext& ctx = Belt::cast(context);
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;

	if (ctx.item_count_)
	{
		// 绘制第一个物品
		const float item_pos = min(ctx.item_pos_[ctx.first_], 1.0f);
		const auto p0 = offset_right(context.direction, map.cell_size, item_pos, x0, y0, x1, y1);
		if (ctx.item_types_[ctx.first_] == ItemType::dye)
		{
			draw_color(p0.x, p0.y, map.cell_size, renderer, ctx.dyes_[ctx.first_]);
		}
		else
		{
			draw_item(p0.x, p0.y, map.cell_size, renderer, ctx.shapes_[ctx.first_]);
		}
	}
	if (ctx.item_count_ == 2)
	{
		// 绘制第二个物品
		const float item_pos = min(ctx.item_pos_[ctx.second_], 0.5f);
		const auto p0 = offset_right(context.direction, map.cell_size, item_pos, x0, y0, x1, y1);
		if (ctx.item_types_[ctx.second_] == ItemType::dye)
		{
			draw_color(p0.x, p0.y, map.cell_size, renderer, ctx.dyes_[ctx.second_]);
		}
		else
		{
			draw_item(p0.x, p0.y, map.cell_size, renderer, ctx.shapes_[ctx.second_]);
		}
	}
}

const string& BeltRightRenderer::get_building_tex(const int index) const
{
	return tex_right_[index];
}

Vec2 BeltRightRenderer::offset_right(const Side direction, const float cell_size, const float p,
                                     const float x0, const float y0, const float x1, const float y1)
{
	if (p <= 0.3f)
	{
		// 上升 0.3 -> 0.2
		const float pp = p / 3 * 2;
		switch (direction)
		{
		case Side::up:
			return {x0 + 0.3f * cell_size, y0 + (0.7f - pp) * cell_size};
		case Side::down:
			return {x0 + 0.3f * cell_size, y0 + (-0.1f + pp) * cell_size};
		case Side::left:
			return {x0 + (0.7f - pp) * cell_size, y0 + 0.3f * cell_size};
		case Side::right:
			return {x0 + (-0.1f + pp) * cell_size, y0 + 0.3f * cell_size};
		}
	}
	else if (p <= 0.7f)
	{
		// 斜向 0.4 -> 0.2
		const float pp = (p - 0.3f) / 2;
		switch (direction)
		{
		case Side::up:
			return {x0 + (0.3f + pp) * cell_size, y0 + (0.5f - pp) * cell_size};
		case Side::down:
			return {x0 + (0.3f - pp) * cell_size, y0 + (0.1f + pp) * cell_size};
		case Side::left:
			return {x0 + (0.5f - pp) * cell_size, y0 + (0.3f - pp) * cell_size};
		case Side::right:
			return {x0 + (0.1f + pp) * cell_size, y0 + (0.3f + pp) * cell_size};
		}
	}
	else
	{
		// 横向 0.3 -> 0.4
		const float pp = (p - 0.7f) / 3 * 4;
		switch (direction)
		{
		case Side::up:
			return {x0 + (0.5f + pp) * cell_size, y0 + 0.3f * cell_size};
		case Side::down:
			return {x0 + (0.1f - pp) * cell_size, y0 + 0.3f * cell_size};
		case Side::left:
			return {x0 + 0.3f * cell_size, y0 + (0.1f - pp) * cell_size};
		case Side::right:
			return {x0 + 0.3f * cell_size, y0 + (0.5f + pp) * cell_size};
		}
	}
}
