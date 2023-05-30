#include "BeltRenderer.h"

#include "Belt.h"
#include "GameLogic.h"
#include "GameRenderer.h"
#include "MouseHelper.h"

void BeltRenderer::draw_building(const int row, const int col, const BuildingContext& context, GameRenderer& renderer,
                                 const GameMap& map) const
{
	renderer.tex_drawer.tex(renderer.buildings_small);
	const BeltContext& ctx = Belt::cast(context);
	const int index = (current_game->timer().running_ms / delta_time_) % 14;
	auto& [u, v, w, h] = get_building_uv(index, renderer);
	const float x0 = renderer.edge_pos[col].x;
	const float y0 = renderer.edge_pos[row].y;
	const float x1 = renderer.edge_pos[col + 1].x;
	const float y1 = renderer.edge_pos[row + 1].y;
	renderer.tex_drawer.push(x0, y0, x1, y1, u, v, w, h, context.direction);
}

void BeltRenderer::draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const
{
	auto& [u, v, w, h] = get_holding_uv(renderer);
	renderer.tex_drawer.tex(renderer.buildings_small);
	renderer.tex_drawer.push(x, y, x + map.cell_size, y + map.cell_size, u, v, w, h, direction);
}

void BeltRenderer::draw_icon(float x, float y, float size, GameRenderer& renderer) const
{
	renderer.tex_drawer.tex(renderer.icons);
	renderer.tex_drawer.alpha(ICON_ALPHA);
	const float mouse_x = MouseHelper::x();
	const float mouse_y = MouseHelper::y();
	const bool selected = !current_game->current_building
		&& is_in(x, mouse_x, BUTTON_SIZE)
		&& is_in(y, mouse_y, BUTTON_SIZE);
	const auto& [u, v, w, h] = renderer.icons["belt.png"];
	renderer.tex_drawer.push(x + ICON_PADDING, y + ICON_PADDING,
	                         x + BUTTON_SIZE - ICON_PADDING, y + BUTTON_SIZE - ICON_PADDING,
	                         u, v, w, h, Side::up, selected);
}

const Rect& BeltDirectRenderer::get_building_uv(const int index, GameRenderer& renderer) const
{
	return renderer.buildings_small[tex_forward_[index]];
}

const Rect& BeltDirectRenderer::get_holding_uv(const GameRenderer& renderer) const
{
	return renderer.buildings_small["belt_top_blue.png"];
}

const Rect& BeltLeftRenderer::get_building_uv(const int index, GameRenderer& renderer) const
{
	return renderer.buildings_small[tex_left_[index]];
}

const Rect& BeltLeftRenderer::get_holding_uv(const GameRenderer& renderer) const
{
	return renderer.buildings_small["belt_left_blue.png"];
}

const Rect& BeltRightRenderer::get_building_uv(const int index, GameRenderer& renderer) const
{
	return renderer.buildings_small[tex_right_[index]];
}

const Rect& BeltRightRenderer::get_holding_uv(const GameRenderer& renderer) const
{
	return renderer.buildings_small["belt_right_blue.png"];
}
