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

	// 渲染资源
	auto& building = dynamic_cast<const Miner&>(context.building);
	auto& ctx = building.cast(context);
	if (const auto res = map.get_resource(row, col); res != ResourceType::none)
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
			const auto [p0, p1] = offset_item(context.direction, map.cell_size, p, x0, y0, x1, y1);
			renderer.tex_drawer.push(p0.x, p0.y, p1.x, p1.y, renderer.atlas, resource_icon(res), Side::up);
		}
	}

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

MinerRenderer::p2 MinerRenderer::offset_item(const Side direction, const float cell_size, const float p,
                                             const float x0, const float y0, const float x1, const float y1)
{
	// 0.0 -> 0.1
	const float pp = p * 0.1f;
	switch (direction)
	{
	case Side::up:
		return {
			{x0 + 0.25f * cell_size, y0 - (pp - 0.3f) * cell_size},
			{x1 - 0.25f * cell_size, y0 - (pp + 0.2f) * cell_size}
		};
	case Side::down:
		return {
			{x0 + 0.25f * cell_size, y1 + (pp - 0.3f) * cell_size},
			{x1 - 0.25f * cell_size, y1 + (pp + 0.2f) * cell_size}
		};
	case Side::left:
		return {
			{x0 - (0.5f - pp) * cell_size, y0 + 0.25f * cell_size},
			{x0 + pp * cell_size, y1 - 0.25f * cell_size}
		};
	case Side::right:
		return {
			{x1 + pp * cell_size, y0 + 0.25f * cell_size},
			{x1 - (0.5f - pp) * cell_size, y1 - 0.25f * cell_size}
		};
	}
	return {};
}
