#include "UndergroundBelt2Renderer.h"

#include "BuildingContext.h"
#include "GameRenderer.h"
#include "UndergroundBelt2.h"

void UndergroundBelt2Renderer::draw_building(const int row, const int col, const BuildingContext& context,
                                             GameRenderer& renderer, const GameMap& map) const
{
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas,
	                         "underground_belt_exit.png", context.direction);
}

void UndergroundBelt2Renderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
                                            const GameMap& map) const
{
	renderer.tex_drawer.push(x - EXT_SIZE, y - EXT_SIZE, x + map.cell_size + EXT_SIZE, y + map.cell_size + EXT_SIZE,
	                         renderer.atlas, "underground_belt_exit_blue.png", direction);
}

void UndergroundBelt2Renderer::draw_items_in_building(int row, int col, const BuildingContext& context,
                                                      GameRenderer& renderer, const GameMap& map) const
{
	const auto& ctx = UndergroundBelt2::cast(context);
	if (ctx.type_ == ItemType::shape)
	{
		draw_output_item(row, col, map.cell_size, context.direction, renderer, ctx.shapes_, ctx);
	}
	else if (ctx.type_ == ItemType::dye)
	{
		draw_output_color(row, col, map.cell_size, context.direction, renderer, ctx.color_, ctx);
	}
}
