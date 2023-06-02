#include "RotaterRenderer.h"

#include "BuildingContext.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "Rotater.h"

void RotaterRenderer::draw_building(const int row, const int col, const BuildingContext& context,
                                    GameRenderer& renderer, const GameMap& map) const
{
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas, tex_building_,
	                         context.direction);
}

void RotaterRenderer::draw_holding(const float x, const float y, const Side direction, GameRenderer& renderer,
                                   const GameMap& map) const
{
	renderer.tex_drawer.push(x - EXT_SIZE, y - EXT_SIZE, x + map.cell_size + EXT_SIZE, y + map.cell_size + EXT_SIZE,
	                         renderer.atlas, tex_holding_, direction);
}

void RotaterRenderer::draw_icon(const float x, const float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
	                         x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
	                         renderer.atlas, "rotater_icon.png", Side::up);
}

void RotaterRenderer::draw_items_in_building(const int row, const int col, const BuildingContext& context,
                                             GameRenderer& renderer, const GameMap& map) const
{
	const auto& ctx = static_cast<const RotaterContext&>(context);
	draw_output_item(row, col, map.cell_size, context.direction, renderer, ctx.shapes_, ctx);
}

const RotaterRenderer& RotaterRenderer::cw()
{
	static RotaterRenderer renderer{"rotater.png", "rotater_blue.png"};
	return renderer;
}

const RotaterRenderer& RotaterRenderer::ccw()
{
	static RotaterRenderer renderer{"rotater-ccw.png", "rotater-ccw_blue.png"};
	return renderer;
}
