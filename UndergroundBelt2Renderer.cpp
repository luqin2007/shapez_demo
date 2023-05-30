#include "UndergroundBelt2Renderer.h"

#include "BuildingContext.h"
#include "GameRenderer.h"

void UndergroundBelt2Renderer::draw_building(const int row, const int col, const BuildingContext& context,
                                             GameRenderer& renderer, const GameMap& map) const
{
	renderer.tex_drawer.tex(renderer.buildings_small);
	auto& [u, v, w, h] = renderer.buildings_small["underground_belt_exit.png"];
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0, y0, x1, y1, u, v, w, h, context.direction);
}

void UndergroundBelt2Renderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
                                            const GameMap& map) const
{
	auto& [u, v, w, h] = renderer.buildings_small["underground_belt_exit_blue.png"];
	renderer.tex_drawer.tex(renderer.buildings_small);
	renderer.tex_drawer.push(x, y, x + map.cell_size, y + map.cell_size, u, v, w, h, direction);
}

void UndergroundBelt2Renderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
}
