#pragma once

#include "Atlas.h"
#include "BuildingRenderer.h"

class RotaterRenderer final : public BuildingRenderer
{
public:
	void draw_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                   const GameMap& map) const override;
	void draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const override;
	void draw_icon(float x, float y, float size, GameRenderer& renderer) const override;
	void draw_overlay(int row, int col,
	                  const BuildingContext& context, GameRenderer& renderer, const GameMap& map) const override;

	static const RotaterRenderer& cw();
	static const RotaterRenderer& ccw();

private:
	RotaterRenderer(string tex_building, string tex_holding)
		: tex_building_(std::move(tex_building)), tex_holding_(std::move(tex_holding))
	{
	}

	const string tex_building_, tex_holding_;
};
