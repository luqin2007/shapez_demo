#pragma once

#include "BuildingRenderer.h"

class UndergroundBelt2Renderer final : public BuildingRenderer
{
public:
	void draw_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                   const GameMap& map) const override;
	void draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const override;
	void draw_items_in_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                            const GameMap& map) const override;

	void draw_icon(float x, float y, float size, GameRenderer& renderer) const override
	{
	}
};
