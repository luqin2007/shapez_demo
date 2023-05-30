#include "MinerRenderer.h"

#include "BuildingContext.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "MouseHelper.h"

void MinerRenderer::draw_building(const int row, const int col, const BuildingContext& context,
                                  GameRenderer& renderer, const GameMap& map) const
{
	renderer.tex_drawer.tex(renderer.buildings_small);
	const Rect* r;
	if (current_game && current_game->map().get_resource(context.pos) != ResourceType::none)
	{
		// 可挖掘
		r = &renderer.buildings_small["miner-chainable.png"];
	}
	else
	{
		// 无资源
		r = &renderer.buildings_small["miner.png"];
	}
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0, y0, x1, y1, r->u, r->v, r->w, r->h, context.direction);
}

void MinerRenderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
									const GameMap& map) const
{
	auto& [u, v, w, h] = renderer.buildings_small["miner_blue.png"];
	renderer.tex_drawer.tex(renderer.buildings_small);
	renderer.tex_drawer.push(x, y, x + map.cell_size, y + map.cell_size, u, v, w, h, direction);
}

void MinerRenderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.tex(renderer.icons);
	renderer.tex_drawer.alpha(ICON_ALPHA);
	const float mouse_x = MouseHelper::x();
	const float mouse_y = MouseHelper::y();
	const bool selected = !current_game->current_building
		&& is_in(x, mouse_x, BUTTON_SIZE)
		&& is_in(y, mouse_y, BUTTON_SIZE);
	const auto& [u, v, w, h] = renderer.icons["miner.png"];
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
							 x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
							 u, v, w, h, Side::up, selected);
}
