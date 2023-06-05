#include "HubRenderer.h"

#include "BuildingContext.h"
#include "GameRenderer.h"
#include "Hub.h"

void HubRenderer::draw_building(const int row, const int col, const BuildingContext& context, GameRenderer& renderer,
                                const GameMap& map) const
{
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 4].x;
	const float y1 = renderer.edge_pos[row + 4].y;
	renderer.tex_drawer.push(x0 - EXT_SIZE, y0 - EXT_SIZE, x1 + EXT_SIZE, y1 + EXT_SIZE, renderer.atlas, "hub.png",
	                         context.direction);
	renderer.tex_drawer.draw();

	// 需求物品
	const auto& ctx = static_cast<const HubContext&>(context);
	ctx.shapes.draw(renderer.atlas, renderer.tex_drawer,
	                x0 + map.cell_size * 0.8f,
	                y0 + map.cell_size * 1.2f,
	                x0 + map.cell_size * 2.0f,
	                y0 + map.cell_size * 2.4f);

	// 开始文本绘制
	auto& font = renderer.font_drawer;
	font.begin(renderer.atlas);
	char ss[100];
	const float scale = map.cell_size / 100;
	// 文本
	font.color(1, 1, 1, 1);
	font.push("LVL", x0 + 0.84f * map.cell_size, y0 + 0.55 * map.cell_size, scale * 0.38f);
	sprintf_s(ss, "%d", ctx.level);
	font.push(ss, x0 + 0.84f * map.cell_size, y0 + 0.75 * map.cell_size, scale * 0.65f);
	font.color(0.39f, 0.4f, 0.43f, 1);
	font.push("DELIVER", x0 + 2.2f * map.cell_size, y0 + 0.7f * map.cell_size, scale * 0.6f);
	sprintf_s(ss, "%d", ctx.accept_count);
	font.push(ss, x0 + map.cell_size * 2.7f, y0 + map.cell_size * 1.3f, scale * 2);
	font.color(0.65f, 0.65f, 0.69f, 1);
	sprintf_s(ss, "/ %d", ctx.total_count);
	font.push(ss, x0 + map.cell_size * 2.8f, y0 + map.cell_size * 2.3f,
	          scale * 1.1f);
	font.draw();

	// 恢复环境
	renderer.tex_drawer.begin();
}
