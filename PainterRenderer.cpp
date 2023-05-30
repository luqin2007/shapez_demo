#include "PainterRenderer.h"

#include "BuildingContext.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "MouseHelper.h"

void PainterRenderer::draw_building(const int row, const int col, const BuildingContext& context,
									 GameRenderer& renderer, const GameMap& map) const
{
	renderer.tex_drawer.tex(renderer.buildings_middle);
	auto& [u, v, w, h] = renderer.buildings_middle["painter.png"];
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 2].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0, y0, x1, y1, u, v, w, h, context.direction);
}

void PainterRenderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
									const GameMap& map) const
{
	auto& [u, v, w, h] = renderer.buildings_middle["painter_blue.png"];
	renderer.tex_drawer.tex(renderer.buildings_middle);
	renderer.tex_drawer.push(x, y, x + map.cell_size * 2, y + map.cell_size, u, v, w, h, direction);
}

void PainterRenderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.tex(renderer.icons);
	renderer.tex_drawer.alpha(ICON_ALPHA);
	const float mouse_x = MouseHelper::x();
	const float mouse_y = MouseHelper::y();
	const bool selected = !current_game->current_building
		&& is_in(x, mouse_x, BUTTON_SIZE)
		&& is_in(y, mouse_y, BUTTON_SIZE);
	const auto& [u, v, w, h] = renderer.icons["painter.png"];
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
							 x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
							 u, v, w, h, Side::up, selected);
}
