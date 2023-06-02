#include "MinerRenderer.h"

#include "BuildingContext.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "Miner.h"

void MinerRenderer::draw_building(const int row, const int col, const BuildingContext& context,
                                  GameRenderer& renderer, const GameMap& map) const
{
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;

	// 渲染建筑
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas,
	                         "miner.png", context.direction);
}

void MinerRenderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
                                 const GameMap& map) const
{
	renderer.tex_drawer.push(x - EXT_SIZE, y - EXT_SIZE, x + map.cell_size + EXT_SIZE, y + map.cell_size + EXT_SIZE,
	                         renderer.atlas, "miner_blue.png", direction);
}

void MinerRenderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
	                         x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
	                         renderer.atlas, "miner_icon.png", Side::up);
}

void MinerRenderer::draw_items_in_building(const int row, const int col, const BuildingContext& context,
                                           GameRenderer& renderer, const GameMap& map) const
{
	auto& ctx = Miner::cast(context);
	if (const auto res = map.get_resource(row, col); res != ResourceType::none)
	{
		draw_output_texture(row, col, map.cell_size, context.direction, renderer, resource_icon(res), ctx);
	}
}
