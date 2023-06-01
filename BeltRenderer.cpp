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
	draw_items(x0, y0, x1, y1, map.cell_size, ctx, renderer);
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

const string& BeltDirectRenderer::get_building_tex(const int index) const
{
	return tex_forward_[index];
}

void BeltDirectRenderer::draw_items(const float x0, const float y0, const float x1, float y1, const float cell_size,
                                    const BeltContext& context, GameRenderer& renderer) const
{
	if (context.item_count_)
	{
		// 绘制第一个物品
		const float item_pos = min(context.item_pos_[context.first_], 1.0f) - 0.1f;
		const float ix0 = x0 + cell_size * 0.25f;
		const float ix1 = x1 - cell_size * 0.25f;
		const float iy0 = y0 + cell_size * 0.5f * item_pos;
		const float iy1 = iy0 + cell_size * 0.5f;
		if (context.item_types_[context.first_] == ItemType::dye)
		{
			renderer.tex_drawer.push(ix0, iy0, ix1, iy1, renderer.atlas, color_icon(context.dyes_[context.first_]),
			                         context.direction);
		}
		else
		{
			context.shapes_[context.first_].draw(renderer.atlas, renderer.tex_drawer, ix0, iy0, ix1, iy1,
			                                     context.direction);
		}
	}
	if (context.item_count_ == 2)
	{
		// 绘制第二个物品
		const float item_pos = min(context.item_pos_[context.second_], 0.5f) - 0.1f;
		const float ix0 = x0 + cell_size * 0.25f;
		const float ix1 = x1 - cell_size * 0.25f;
		const float iy0 = y0 + cell_size * 0.5f * item_pos;
		const float iy1 = iy0 + cell_size * 0.5f;
		if (context.item_types_[context.first_] == ItemType::dye)
		{
			renderer.tex_drawer.push(ix0, iy0, ix1, iy1, renderer.atlas, color_icon(context.dyes_[context.first_]),
			                         context.direction);
		}
		else
		{
			context.shapes_[context.first_].draw(renderer.atlas, renderer.tex_drawer, ix0, iy0, ix1, iy1,
			                                     context.direction);
		}
	}
}

const string& BeltLeftRenderer::get_building_tex(const int index) const
{
	return tex_left_[index];
}

void BeltLeftRenderer::draw_items(const float x0, const float y0, const float x1, float y1, const float cell_size,
                                  const BeltContext& context, GameRenderer& renderer) const
{
	if (context.item_count_)
	{
		// 绘制第一个物品
		float item_pos = min(context.item_pos_[context.first_], 1.0f);

		float ix0;
		float ix1;
		float iy0;
		float iy1;
		if (item_pos <= 0.5f)
		{
			// 直路
			item_pos -= 0.1f;
			ix0 = x0 + cell_size * 0.25f;
			ix1 = x1 - cell_size * 0.25f;
			iy0 = y0 + cell_size * 0.5f * item_pos;
			iy1 = iy0 + cell_size * 0.5f;
		}
		else
		{
			// 弯路
			item_pos -= 0.5f;
			ix0 = x0 + cell_size * (0.25f + item_pos);
			ix1 = x1 - cell_size * 0.25f;
			iy0 = y0 + cell_size * 0.2f;
			iy1 = iy0 + cell_size * 0.5f;
		}

		if (context.item_types_[context.first_] == ItemType::dye)
		{
			renderer.tex_drawer.push(ix0, iy0, ix1, iy1, renderer.atlas, color_icon(context.dyes_[context.first_]),
			                         context.direction);
		}
		else
		{
			context.shapes_[context.first_].draw(renderer.atlas, renderer.tex_drawer, ix0, iy0, ix1, iy1,
			                                     context.direction);
		}
	}
	if (context.item_count_ == 2)
	{
		// 绘制第二个物品
		const float item_pos = min(context.item_pos_[context.second_], 0.5f) - 0.1f;
		const float ix0 = x0 + cell_size * 0.25f;
		const float ix1 = x1 - cell_size * 0.25f;
		const float iy0 = y0 + cell_size * 0.5f * item_pos;
		const float iy1 = iy0 + cell_size * 0.5f;
		if (context.item_types_[context.first_] == ItemType::dye)
		{
			renderer.tex_drawer.push(ix0, iy0, ix1, iy1, renderer.atlas, color_icon(context.dyes_[context.first_]),
			                         context.direction);
		}
		else
		{
			context.shapes_[context.first_].draw(renderer.atlas, renderer.tex_drawer, ix0, iy0, ix1, iy1,
			                                     context.direction);
		}
	}
}

const string& BeltRightRenderer::get_building_tex(const int index) const
{
	return tex_right_[index];
}

void BeltRightRenderer::draw_items(float x0, float y0, float x1, float y1, float cell_size,
                                   const BeltContext& context, GameRenderer& renderer) const
{
	if (context.item_count_)
	{
		// 绘制第一个物品
		float item_pos = min(context.item_pos_[context.first_], 1.0f);

		float ix0;
		float ix1;
		float iy0;
		float iy1;
		if (item_pos <= 0.5f)
		{
			// 直路
			item_pos -= 0.1f;
			ix0 = x0 + cell_size * 0.25f;
			ix1 = x1 - cell_size * 0.25f;
			iy0 = y0 + cell_size * 0.5f * item_pos;
			iy1 = iy0 + cell_size * 0.5f;
		}
		else
		{
			// 弯路
			item_pos -= 0.5f;
			ix0 = x0 + cell_size * (0.25f - item_pos);
			ix1 = x1 - cell_size * 0.25f;
			iy0 = y0 + cell_size * 0.2f;
			iy1 = iy0 + cell_size * 0.5f;
		}

		if (context.item_types_[context.first_] == ItemType::dye)
		{
			renderer.tex_drawer.push(ix0, iy0, ix1, iy1, renderer.atlas, color_icon(context.dyes_[context.first_]),
									 context.direction);
		}
		else
		{
			context.shapes_[context.first_].draw(renderer.atlas, renderer.tex_drawer, ix0, iy0, ix1, iy1,
												 context.direction);
		}
	}
	if (context.item_count_ == 2)
	{
		// 绘制第二个物品
		const float item_pos = min(context.item_pos_[context.second_], 0.5f) - 0.1f;
		const float ix0 = x0 + cell_size * 0.25f;
		const float ix1 = x1 - cell_size * 0.25f;
		const float iy0 = y0 + cell_size * 0.5f * item_pos;
		const float iy1 = iy0 + cell_size * 0.5f;
		if (context.item_types_[context.first_] == ItemType::dye)
		{
			renderer.tex_drawer.push(ix0, iy0, ix1, iy1, renderer.atlas, color_icon(context.dyes_[context.first_]),
									 context.direction);
		}
		else
		{
			context.shapes_[context.first_].draw(renderer.atlas, renderer.tex_drawer, ix0, iy0, ix1, iy1,
												 context.direction);
		}
	}
}
