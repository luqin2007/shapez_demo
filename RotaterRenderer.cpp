#include "RotaterRenderer.h"

#include "BuildingContext.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "MouseHelper.h"

void RotaterRenderer::draw_building(const int row, const int col, const BuildingContext& context,
                                    GameRenderer& renderer, const GameMap& map) const
{
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas, get_building_tex(), context.direction);
}

void RotaterRenderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
                                   const GameMap& map) const
{
	renderer.tex_drawer.push(x - EXT_SIZE, y - EXT_SIZE, x + map.cell_size + EXT_SIZE, y + map.cell_size + EXT_SIZE,
							 renderer.atlas, get_holding_tex(), direction);
}

void RotaterRenderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.alpha(ICON_ALPHA);
	const float mouse_x = MouseHelper::x();
	const float mouse_y = MouseHelper::y();
	const bool selected = !current_game->current_building
		&& is_in(x, mouse_x, BUTTON_SIZE)
		&& is_in(y, mouse_y, BUTTON_SIZE);
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
	                         x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
							 renderer.atlas, "rotater_icon.png", Side::up, selected);
}

const string& RotaterCWRenderer::get_building_tex() const
{
	return "rotater.png";
}

const string& RotaterCWRenderer::get_holding_tex() const
{
	return "rotater_blue.png";
}

const string& RotaterCCWRenderer::get_building_tex() const
{
	return "rotater-ccw.png";
}

const string& RotaterCCWRenderer::get_holding_tex() const
{
	return "rotater-ccw_blue.png";
}
