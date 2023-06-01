#pragma once
#include "Atlas.h"
#include "BuildingRenderer.h"
#include "vec.h"

class MinerRenderer final : public BuildingRenderer
{
public:
	typedef std::pair<Vec2, Vec2> p2;

	void draw_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                   const GameMap& map) const override;
	void draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const override;
	void draw_icon(float x, float y, float size, GameRenderer& renderer) const override;

private:
	static p2 offset_item(Side direction, float cell_size, float p, float x0, float y0, float x1, float y1);
};
