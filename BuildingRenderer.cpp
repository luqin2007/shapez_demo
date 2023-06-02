#include "BuildingRenderer.h"

#include "ColoredShapes.h"
#include "GameRenderer.h"
#include "TickableBuilding.h"

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

void BuildingRenderer::draw_output_texture(const int row, const int col, const float cell_size, const Side direction,
                                           GameRenderer& renderer, const string& texture, const TickableContext& ctx)
{
	float p = 0;
	bool draw_res = true;
	if (ctx.status_ == BuildingStatus::blocking)
	{
		p = 1;
	}
	else if (ctx.status_ == BuildingStatus::running && ctx.required_time_ - ctx.current_time_ <= 100)
	{
		p = 1 - (ctx.required_time_ - ctx.current_time_) / 100.0f;
	}
	else
	{
		draw_res = false;
	}

	if (draw_res)
	{
		const auto p0 = offset_item(direction, cell_size, p, renderer.edge_pos[col].x, renderer.edge_pos[row].y);
		const float offset = 0.4f * cell_size;
		renderer.tex_drawer.push(p0.x, p0.y, p0.x + offset, p0.y + offset, renderer.atlas, texture);
	}
}

void BuildingRenderer::draw_output_color(const int row, const int col, const float cell_size, const Side direction,
                                         GameRenderer& renderer, const Color color, const TickableContext& ctx)
{
	draw_output_texture(row, col, cell_size, direction, renderer, color_icon(color), ctx);
}

void BuildingRenderer::draw_output_item(const int row, const int col, const float cell_size, const Side direction,
                                        GameRenderer& renderer, const ColoredShapes& item, const TickableContext& ctx)
{
	float p = 0;
	bool draw_res = true;
	if (ctx.status_ == BuildingStatus::blocking)
	{
		p = 1;
	}
	else if (ctx.status_ == BuildingStatus::running && ctx.required_time_ - ctx.current_time_ <= 100)
	{
		p = 1 - (ctx.required_time_ - ctx.current_time_) / 100.0f;
	}
	else
	{
		draw_res = false;
	}

	if (draw_res)
	{
		const auto p0 = offset_item(direction, cell_size, p, renderer.edge_pos[col].x, renderer.edge_pos[row].y);
		const float offset = 0.4f * cell_size;
		item.draw(renderer.atlas, renderer.tex_drawer, p0.x, p0.y, p0.x + offset, p0.y + offset);
	}
}

Vec2 BuildingRenderer::offset_item(const Side direction, const float cell_size,
                                   const float p, const float x0, const float y0)
{
	// 0.0 -> 0.1
	const float pp = p * 0.1f;
	switch (direction)
	{
	case Side::up:
		return {x0 + 0.3f * cell_size, y0 - (pp + 0.1f) * cell_size};
	case Side::down:
		return {x0 + 0.3f * cell_size, y0 + (pp + 0.7f) * cell_size};
	case Side::left:
		return {x0 - (pp + 0.1f) * cell_size, y0 + 0.3f * cell_size};
	case Side::right:
		return {x0 + (pp + 0.7f) * cell_size, y0 + 0.3f * cell_size};
	}
	return {};
}
