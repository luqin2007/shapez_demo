#include "BuildingRenderer.h"

#include "ColoredShapes.h"
#include "GameRenderer.h"

using std::string;

void BuildingRenderer::draw_color(const float x0, const float y0, const float cell_size, GameRenderer& renderer,
                                  const Color color)
{
	renderer.tex_drawer.push(x0, y0, x0 + 0.4f * cell_size, y0 + 0.4f * cell_size, renderer.atlas, color_icon(color));
}

void BuildingRenderer::draw_item(const float x0, const float y0, const float cell_size,
								 GameRenderer& renderer, const ColoredShapes& item)
{
	item.draw(renderer.atlas, renderer.tex_drawer, x0, y0, x0 + 0.4f * cell_size, y0 + 0.4f * cell_size);
}
