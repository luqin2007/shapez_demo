#include "HubRenderer.h"

#include "BuildingContext.h"
#include "GameRenderer.h"

void HubRenderer::draw_building(const int row, const int col, const BuildingContext& context, GameRenderer& renderer,
                                const GameMap& map) const
{
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 4].x;
	const float y1 = renderer.edge_pos[row + 4].y;
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas, "hub.png",
	                         context.direction);
}
